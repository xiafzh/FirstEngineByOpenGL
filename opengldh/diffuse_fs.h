#pragma once
#include "ggl.h"

class CShader;
class CDiffuse
{
public:
	CDiffuse();
	virtual ~CDiffuse();

	virtual	void Init(const char*model_path);
	virtual void Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(const char*imagePath);
protected:

	CShader* m_shader;

	glm::mat4 m_model_matrix;
};
