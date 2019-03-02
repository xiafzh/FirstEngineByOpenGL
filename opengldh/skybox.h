#pragma once
#include "shader.h"
#include "vertexbuffer.h"

class CSkyBox 
{
public:
	void Init(const char *imageDir);
	void Draw(glm::vec3& camera_pos, glm::mat4 &V, glm::mat4&P);
private:
	void InitTexture(CShader& shader, const char* dir, const char* name);

	void InitFront();
	void InitBack();
	void InitLeft();
	void InitRight();
	void InitTop();
	void InitBottom();

private:
	CShader * m_shader;
	CVertexBuffer* m_vertex_buffer;
	glm::mat4 m_model_matrix;

	glm::vec3 m_camera_pos;
};