#pragma once
#include "ggl.h"
#include "model.h"

class CModelObjExt : public CModel
{
public:
	CModelObjExt();

	virtual	void Init(const char*model_path);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
};
