#pragma once
#include "ggl.h"

class CVertexBuffer;
class Shader;
class CGround
{
public:
	CGround();

	void Init();
	void Draw(glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix);
private:
	CVertexBuffer * m_vertex_buffer;
	Shader* m_shader;

	glm::mat4 m_model_matrix;
};
