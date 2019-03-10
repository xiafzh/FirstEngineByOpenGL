#pragma once
#include "ggl.h"
#include "model.h"
#include "fbxsdk/include/fbxsdk.h"

class CModelFbx : public CModel
{
public:
	CModelFbx();

	virtual void Init(const char*model_path);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);

private:
	void ImportNode(FbxNode* node);
	void ImportMeterial(FbxNode* node);
	void ImportMesh(FbxMesh* mesh);
};
