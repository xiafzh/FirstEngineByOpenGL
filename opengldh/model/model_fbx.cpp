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

	m_vertex_buffer = new CVertexBuffer();

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


// 
// 	int file_size = 0;
// 	unsigned char* file_content = LoadFileContent(model_path, file_size);
// 	if (nullptr == file_content) return;
// 	
// 	std::vector<SFloatData> positions, texcoords, normals;
// 	std::vector<SVertexDefine> vertexes;
// 
// 	std::stringstream ss_file_content((char*)file_content);
// 	std::string temp_str;
// 
// 	char sz_one_line[256];
// 
// 	while (!ss_file_content.eof()) 
// 	{
// 		memset(sz_one_line, 0, 256);
// 		ss_file_content.getline(sz_one_line, 256);
// 		if (strlen(sz_one_line) > 0)
// 		{
// 			if (sz_one_line[0] == 'v')
// 			{
// 				std::stringstream ss_one_line(sz_one_line);
// 				if (sz_one_line[1] == 't')
// 				{
// 					ss_one_line >> temp_str;
// 					SFloatData SFloatData;
// 					ss_one_line >> SFloatData.v[0];
// 					ss_one_line >> SFloatData.v[1];
// 					texcoords.push_back(SFloatData);
// 					//printf("texcoord : %f,%f\n", SFloatData.v[0], SFloatData.v[1]);
// 				}
// 				else if (sz_one_line[1] == 'n') 
// 				{
// 					ss_one_line >> temp_str;
// 					SFloatData SFloatData;
// 					ss_one_line >> SFloatData.v[0];
// 					ss_one_line >> SFloatData.v[1];
// 					ss_one_line >> SFloatData.v[2];
// 					normals.push_back(SFloatData);
// 					//printf("normal : %f,%f,%f\n", SFloatData.v[0], SFloatData.v[1], SFloatData.v[2]);
// 				}
// 				else 
// 				{
// 					ss_one_line >> temp_str;
// 					SFloatData SFloatData;
// 					ss_one_line >> SFloatData.v[0];
// 					ss_one_line >> SFloatData.v[1];
// 					ss_one_line >> SFloatData.v[2];
// 					positions.push_back(SFloatData);
// 					//printf("position : %f,%f,%f\n", SFloatData.v[0], SFloatData.v[1], SFloatData.v[2]);
// 				}
// 			}
// 			else if (sz_one_line[0] == 'f') 
// 			{
// 				std::stringstream ss_one_line(sz_one_line);
// 				ss_one_line >> temp_str;
// 				std::string vertexStr;
// 				for (int i = 0; i < 3; i++) 
// 				{
// 					ss_one_line >> vertexStr;
// 					size_t pos = vertexStr.find_first_of('/');
// 					std::string posIndexStr = vertexStr.substr(0, pos);
// 					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
// 					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
// 					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
// 					SVertexDefine vd;
// 					vd.pos_index = atoi(posIndexStr.c_str());
// 					vd.texcoord_index = atoi(texcoordIndexStr.c_str());
// 					vd.normal_index = atoi(normalIndexStr.c_str());
// 					vertexes.push_back(vd);
// 				}
// 			}
// 		}
// 	}
// 	delete file_content;
// 
// 	int vertex_cnt = (int)vertexes.size();
// 	m_vertex_buffer = new CVertexBuffer();
// 	m_vertex_buffer->SetSize(vertex_cnt);
// 	for (int i = 0; i < vertex_cnt; ++i)
// 	{
// 		float* temp = positions[vertexes[i].pos_index - 1].v;
// 		m_vertex_buffer->SetPosition(i, temp[0], temp[1], temp[2]);
// 
// 		temp = texcoords[vertexes[i].texcoord_index - 1].v;
// 		m_vertex_buffer->SetTexcoord(i, temp[0], temp[1]);
// 
// 		temp = normals[vertexes[i].normal_index - 1].v;
// 		m_vertex_buffer->SetNormal(i, temp[0], temp[1], temp[2]);
// 	}
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

void CModelFbx::ImportNode(FbxNode* node)
{
	if (nullptr == node) return;

	FbxMesh* mesh = node->GetMesh();
	if (NULL != mesh)
	{
		ImportMeterial(node);
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
			FbxTexture* texture = property.GetSrcObject<FbxTexture>();
			if (nullptr != texture)
			{
				
				printf("texture name: %s\n", texture->GetName());
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

	m_vertex_buffer->SetSize(polygon_idx_cnt);

	int curr_polygon_idx = 0;
	for (int i = 0; i < polygon_cnt; ++i, ++curr_polygon_idx)
	{
		int curr_polygon_idx_cnt = mesh->GetPolygonSize(i);
		for (int j = 0; j < curr_polygon_idx_cnt; ++j)
		{
			int vertex_idx = mesh->GetPolygonVertex(i, j);

			m_vertex_buffer->SetPosition(curr_polygon_idx, (float)control_ponits[vertex_idx].mData[0]
				, (float)control_ponits[vertex_idx].mData[1]
				, (float)control_ponits[vertex_idx].mData[2]
			);

			FbxVector4 normal;
			if (mesh->GetPolygonVertexNormal(i, j, normal))
			{
				m_vertex_buffer->SetNormal(curr_polygon_idx
					, (float)normal.mData[0]
					, (float)normal.mData[1]
					, (float)normal.mData[2]
				);
			}

			FbxVector2 uv;
			bool flag = true;
			if (mesh->GetPolygonVertexUV(i, j, uv_name.GetItemAt(0)->mString.Buffer(), uv, flag))
			{
				m_vertex_buffer->SetTexcoord(curr_polygon_idx
					, (float)uv.mData[0]
					, (float)uv.mData[1]
				);
			}
		}

	}
}
