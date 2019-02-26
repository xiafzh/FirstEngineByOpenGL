#pragma once
#include "ggl.h"

class CVertexBuffer;
class CShader;
class CModel
{
public:
	CModel();

	void Init(const char*model_path);
	void Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);
	void SetPosition(float x, float y, float z);
	void SetTexture(const char*imagePath);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
private:
	CVertexBuffer * m_vertex_buffer;
	CShader* m_shader;

	glm::mat4 m_model_matrix;
};
