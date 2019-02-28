#pragma once
#include "vertexbuffer.h"
#include "shader.h"
class CParticleSystem
{
public:
	CParticleSystem();
	void Init(float x, float y, float z);
	void Draw(glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix);
private:
	CVertexBuffer *m_vertex_buffer;
	CShader *m_shader;
	glm::mat4 m_model_matrix;
};