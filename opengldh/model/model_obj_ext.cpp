#include "model_obj_ext.h"
#include "utils.h"
#include "../vertexbuffer.h"
#include "../shader.h"

CModelObjExt::CModelObjExt()
{

}

void CModelObjExt::Init(const char*model_path)
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

	int file_size = 0;
	unsigned char* file_content = LoadFileContent(model_path, file_size);
	if (nullptr == file_content) return;
	
	std::vector<SFloatData> positions, texcoords, normals;
	std::vector<SVertexDefine> vertexes;

	std::stringstream ss_file_content((char*)file_content);
	std::string temp_str;

	char sz_one_line[256];

	while (!ss_file_content.eof()) 
	{
		memset(sz_one_line, 0, 256);
		ss_file_content.getline(sz_one_line, 256);
		if (strlen(sz_one_line) > 0)
		{
			if (sz_one_line[0] == 'v')
			{
				std::stringstream ss_one_line(sz_one_line);
				if (sz_one_line[1] == 't')
				{
					ss_one_line >> temp_str;
					SFloatData SFloatData;
					ss_one_line >> SFloatData.v[0];
					ss_one_line >> SFloatData.v[1];
					texcoords.push_back(SFloatData);
					//printf("texcoord : %f,%f\n", SFloatData.v[0], SFloatData.v[1]);
				}
				else if (sz_one_line[1] == 'n') 
				{
					ss_one_line >> temp_str;
					SFloatData SFloatData;
					ss_one_line >> SFloatData.v[0];
					ss_one_line >> SFloatData.v[1];
					ss_one_line >> SFloatData.v[2];
					normals.push_back(SFloatData);
					//printf("normal : %f,%f,%f\n", SFloatData.v[0], SFloatData.v[1], SFloatData.v[2]);
				}
				else 
				{
					ss_one_line >> temp_str;
					SFloatData SFloatData;
					ss_one_line >> SFloatData.v[0];
					ss_one_line >> SFloatData.v[1];
					ss_one_line >> SFloatData.v[2];
					positions.push_back(SFloatData);
					//printf("position : %f,%f,%f\n", SFloatData.v[0], SFloatData.v[1], SFloatData.v[2]);
				}
			}
			else if (sz_one_line[0] == 'f') 
			{
				std::stringstream ss_one_line(sz_one_line);
				ss_one_line >> temp_str;
				std::string vertexStr;
				for (int i = 0; i < 3; i++) 
				{
					ss_one_line >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					SVertexDefine vd;
					vd.pos_index = atoi(posIndexStr.c_str());
					vd.texcoord_index = atoi(texcoordIndexStr.c_str());
					vd.normal_index = atoi(normalIndexStr.c_str());
					vertexes.push_back(vd);
				}
			}
		}
	}
	delete file_content;

	int vertex_cnt = (int)vertexes.size();
	CVertexBuffer* new_vertex_buffer = new CVertexBuffer();
	m_vertex_buffers.push_back(new_vertex_buffer);
	new_vertex_buffer->SetSize(vertex_cnt);
	for (int i = 0; i < vertex_cnt; ++i)
	{
		float* temp = positions[vertexes[i].pos_index - 1].v;
		new_vertex_buffer->SetPosition(i, temp[0], temp[1], temp[2]);

		temp = texcoords[vertexes[i].texcoord_index - 1].v;
		new_vertex_buffer->SetTexcoord(i, temp[0], temp[1]);

		temp = normals[vertexes[i].normal_index - 1].v;
		new_vertex_buffer->SetNormal(i, temp[0], temp[1], temp[2]);
	}
	m_shader = new CShader();
	m_shader->Init("Res/diffuse_vs.vs", "Res/diffuse_vs.fs");

	m_shader->SetVec4("U_LightPos", 1.0f, 1.0f, 1.0f, 0.0f);
	m_shader->SetVec4("U_AmbientLightColor", 1.0f, 1.0f, 1.0f, 1.0f);
	m_shader->SetVec4("U_DiffuseLightColor", 1.0f, 1.0f, 1.0f, 1.0f);
	//m_shader->SetVec4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	m_shader->SetVec4("U_CameraPos", 0.0f, 0.0f, 0.0f, 1.0f);
	m_shader->SetVec4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);
	SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
	SetDiffuseMaterial(0.5f, 0.5f, 0.5f, 1.0f);
	//SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
}


void CModelObjExt::SetAmbientMaterial(float r, float g, float b, float a)
{
	m_shader->SetVec4("U_AmbientMaterial", r, g, b, a);
}
void CModelObjExt::SetDiffuseMaterial(float r, float g, float b, float a)
{
	m_shader->SetVec4("U_DiffuseMaterial", r, g, b, a);
}
void CModelObjExt::SetSpecularMaterial(float r, float g, float b, float a)
{
	m_shader->SetVec4("U_SpecularMaterial", r, g, b, a);
}
