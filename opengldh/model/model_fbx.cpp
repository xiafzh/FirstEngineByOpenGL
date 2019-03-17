#include "model_fbx.h"
#include "utils.h"
#include "../vertexbuffer.h"
#include "../shader.h"

#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

CModelFbx::CModelFbx()
{

}

void CModelFbx::Init(const char*model_path)
{
	struct SFloatData
	{
		float v[3];
	};

	struct SVertexDefine
	{
		int pos_index;
		int texcoord_index;
		int normal_index;
	};
	
	FbxManager* fbx_manager = FbxManager::Create();
	FbxIOSettings* fbx_iosettting = FbxIOSettings::Create(fbx_manager, IOSROOT);
	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");

	fbx_manager->SetIOSettings(fbx_iosettting);

	if (fbx_importer->Initialize(model_path, -1, fbx_manager->GetIOSettings()))
	{
		FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
		fbx_importer->Import(fbx_scene);

		FbxNode* root_node = fbx_scene->GetRootNode();
		ImportNode(root_node);

		fbx_scene->Destroy();
	}

	fbx_importer->Destroy();
	fbx_iosettting->Destroy();
	fbx_manager->Destroy();

	m_shader = new CShader();
	m_shader->Init("Res/model.vs", "Res/model.fs");
	
	m_shader->SetVec4("U_LightPos", 0.0f, 1.0f, 1.0f, 0.0f);
	m_shader->SetVec4("U_LightAmbient", 1.0f, 1.0f, 1.0f, 1.0f);
	m_shader->SetVec4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	m_shader->SetVec4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	m_shader->SetVec4("U_CameraPos", 0.0f, 0.0f, 0.0f, 1.0f);
	m_shader->SetVec4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);
	SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	SetDiffuseMaterial(0.6f, 0.6f, 0.6f, 1.0f);
	SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
}

void CModelFbx::SetAmbientMaterial(float r, float g, float b, float a) 
{
	m_shader->SetVec4("U_AmbientMaterial", r, g, b, a);
}
void CModelFbx::SetDiffuseMaterial(float r, float g, float b, float a) 
{
	m_shader->SetVec4("U_DiffuseMaterial", r, g, b, a);
}
void CModelFbx::SetSpecularMaterial(float r, float g, float b, float a) 
{
	m_shader->SetVec4("U_SpecularMaterial", r, g, b, a);
}

void CModelFbx::Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix)
{
	glPushMatrix();
	for (int i = 0; i < m_materials.size(); ++i)
	{
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < m_indexes[i].size(); ++j)
		{
			glVertex3fv(m_vertex_buffers[0]->GetVertex(m_indexes[i][j])->Position);
		}
		glEnd();
	}
	glPopMatrix();
}

void CModelFbx::ImportNode(FbxNode* node)
{
	if (nullptr == node) return;

	FbxMesh* mesh = node->GetMesh();
	if (NULL != mesh)
	{
		ImportMeterial(node);
		int meterial_cnt = m_materials.size();
		for (int i=0; i< meterial_cnt; ++i)
		{
			printf("%d %s\n", m_materials[i]->m_type, m_materials[i]->m_diffuse_color_texture);
		}
		for (auto iter = m_material_indexes.begin(); iter != m_material_indexes.end(); ++iter)
		{
			printf("%d -> %d\n", iter->first, iter->second);
		}

		ImportMesh(mesh);
	}

	int chile_node = node->GetChildCount();
	for (int i = 0; i < chile_node; ++i)
	{
		ImportNode(node->GetChild(i));
	}
}

void CModelFbx::ImportMeterial(FbxNode* node)
{
	int material_cnt = node->GetMaterialCount();
	int type = 0;
	for (int i = 0; i < material_cnt; ++i)
	{
		FbxSurfaceMaterial* surface_mat = node->GetMaterial(i);
		if (FbxSurfaceLambert::ClassId == surface_mat->GetClassId())
		{
			type = 0;
		}
		else if (FbxSurfacePhong::ClassId == surface_mat->GetClassId())
		{
			type = 1;
		}
		else
		{
			type = -1;
		}

		FbxProperty property = surface_mat->FindProperty(FbxLayerElement::sTextureChannelNames[0]);
		if (property.IsValid())
		{
			int texture_cnt = property.GetSrcObjectCount<FbxTexture>();
			int curr_mat_idx = -1;
			for (int j = 0; j < texture_cnt; ++j)
			{

			}
			FbxTexture* texture = property.GetSrcObject<FbxTexture>();
			if (nullptr != texture)
			{
				printf("texture name: %s\n", texture->GetName());
				int curr_mat_cnt = (int)m_materials.size();
				for (int k = 0; k < curr_mat_cnt; ++k)
				{
					if (type == 0 && m_materials[k]->m_type == 0)
					{
						if (strcmp(texture->GetName(), m_materials[k]->m_diffuse_color_texture) == 0)
						{
							curr_mat_idx = k;
							break;
						}
					}
					else if (type == 1 && m_materials[k]->m_type == 1)
					{
						if (strcmp(texture->GetName(), m_materials[k]->m_diffuse_color_texture) == 0)
						{
							curr_mat_idx = k;
							break;
						}
					}
				}

				if (curr_mat_idx == -1)
				{
					SMaterialDef* mat = new SMaterialDef();
					mat->m_type = type;
					strcpy(mat->m_diffuse_color_texture, texture->GetName());
					char temp[256] = { 0 };

					mat->m_texture_id = 0; // CreateByPNG
					//Texture::LoadTexture("");
					curr_mat_idx = (int)m_materials.size();
					m_materials.push_back(mat);
				}
				m_material_indexes.insert(std::pair<int, int>(i, curr_mat_idx));
			}
		}
	}
}

void CModelFbx::ImportMesh(FbxMesh* mesh)
{
	int control_point_cnt = mesh->GetControlPointsCount();
	FbxVector4* control_ponits = mesh->GetControlPoints();

	FbxStringList uv_name;
	mesh->GetUVSetNames(uv_name);

	int polygon_cnt = mesh->GetPolygonCount();
	int polygon_idx_cnt = 0;
	for (int i = 0; i < polygon_cnt; ++i)
	{
		polygon_idx_cnt += mesh->GetPolygonSize(i);
	}

	FbxLayerElementArrayTemplate<int> * fbx_material_indices;
	mesh->GetMaterialIndices(&fbx_material_indices);
	FbxGeometryElement::EMappingMode mode = mesh->GetElementMaterial()->GetMappingMode();
	m_indexes.resize(m_materials.size());

	switch (mode)
	{
	case fbxsdk::FbxLayerElement::eNone:
		break;
	case fbxsdk::FbxLayerElement::eByControlPoint:
		break;
	case fbxsdk::FbxLayerElement::eByPolygonVertex:
		break;
	case fbxsdk::FbxLayerElement::eByPolygon:
	{
		for (int i = 0; i < polygon_cnt; ++i)
		{
			int material_index = fbx_material_indices->GetAt(i);
			int material_ref = m_material_indexes[material_index];
 			m_indexes[material_ref].push_back(i * 3);
 			m_indexes[material_ref].push_back(i * 3 + 1);
 			m_indexes[material_ref].push_back(i * 3 + 2);
		}
	}
		break;
	case fbxsdk::FbxLayerElement::eByEdge:
		break;
	case fbxsdk::FbxLayerElement::eAllSame:
		for (int i = 0; i < polygon_cnt; ++i)
		{
			int material_index = fbx_material_indices->GetAt(i);
			int material_ref = m_material_indexes[material_index];
			m_indexes[material_ref].push_back(i * 3);
			m_indexes[material_ref].push_back(i * 3 + 1);
			m_indexes[material_ref].push_back(i * 3 + 2);
		}
		break;
	default:
		break;
	}

	CVertexBuffer* new_vertex_buffer = new CVertexBuffer();
	m_vertex_buffers.push_back(new_vertex_buffer);
	new_vertex_buffer->SetSize(polygon_idx_cnt);

	int curr_polygon_idx = 0;
	for (int i = 0; i < polygon_cnt; ++i, ++curr_polygon_idx)
	{
		int curr_polygon_idx_cnt = mesh->GetPolygonSize(i);
		for (int j = 0; j < curr_polygon_idx_cnt; ++j)
		{
			int vertex_idx = mesh->GetPolygonVertex(i, j);

			new_vertex_buffer->SetPosition(curr_polygon_idx
				, (float)control_ponits[vertex_idx].mData[0]
				, (float)control_ponits[vertex_idx].mData[1]
				, (float)control_ponits[vertex_idx].mData[2]
			);

			FbxVector4 normal;
			if (mesh->GetPolygonVertexNormal(i, j, normal))
			{
				new_vertex_buffer->SetNormal(curr_polygon_idx
					, (float)normal.mData[0]
					, (float)normal.mData[1]
					, (float)normal.mData[2]
				);
			}

			FbxVector2 uv;
			bool flag = true;
			if (mesh->GetPolygonVertexUV(i, j, uv_name.GetItemAt(0)->mString.Buffer(), uv, flag))
			{
				new_vertex_buffer->SetTexcoord(curr_polygon_idx
					, (float)uv.mData[0]
					, (float)uv.mData[1]
				);
			}
		}

	}
}
