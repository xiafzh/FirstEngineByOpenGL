#pragma once
#include "ggl.h"

class CVertexBuffer;
class CShader;
class CModel
{
public:
	CModel();
	virtual ~CModel();

	virtual	void Init(const char*model_path) = 0;
	virtual void Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetTexture(const char*imagePath);
protected:
	std::vector<CVertexBuffer*> m_vertex_buffers;
	CShader* m_shader;

	glm::mat4 m_model_matrix;
};
