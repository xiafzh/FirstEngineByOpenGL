#pragma once
#include "ggl.h"
#include "model.h"
#include "fbxsdk/include/fbxsdk.h"
#include <unordered_map>

struct SMaterialDef
{
	int m_type;
	GLuint m_texture_id;
	char m_diffuse_color_texture[256];
};


class CModelFbx : public CModel
{
public:
	CModelFbx();

	virtual void Init(const char*model_path);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);

	virtual void Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);

protected:
	void ImportNode(FbxNode* node);
	void ImportMeterial(FbxNode* node);
	void ImportMesh(FbxMesh* mesh);

protected:
	char m_fbx_path[256];
	std::vector<SMaterialDef*> m_materials;
	std::unordered_map<int, int> m_material_indexes;
	std::vector< std::vector<int> > m_indexes;
};
