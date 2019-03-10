#pragma once
#include "ggl.h"

class CVertexBuffer;
class CShader;
class CModel
{
public:
	CModel();

	virtual	void Init(const char*model_path) = 0;
	virtual void Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(const char*imagePath);
protected:
	CVertexBuffer * m_vertex_buffer;
	CShader* m_shader;

	glm::mat4 m_model_matrix;
};
