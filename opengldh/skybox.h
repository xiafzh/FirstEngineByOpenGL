#pragma once
#include "shader.h"
#include "vertexbuffer.h"

class CSkyBox 
{
public:
	void Init(const char *imageDir);
	void InitFront(const char *imageDir);
	void InitBack(const char *imageDir);
	void InitLeft(const char *imageDir);
	void InitRight(const char *imageDir);
	void InitTop(const char *imageDir);
	void InitBottom(const char *imageDir);
	void Draw(glm::mat4 &V, glm::mat4&P);

private:
	CShader* m_shader;
	CVertexBuffer* m_vertex_buffer;
	glm::mat4 m_model_matrix;
};