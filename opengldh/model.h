#pragma once
#include "ggl.h"

class CVertexBuffer;
class Shader;
class CModel
{
public:
	CModel();

	void Init(const char*model_path);
	void Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);
	void SetPosition(float x, float y, float z);
private:
	CVertexBuffer * m_vertex_buffer;
	Shader* m_shader;

	glm::mat4 m_model_matrix;
};
