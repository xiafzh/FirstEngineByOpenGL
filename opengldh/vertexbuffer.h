#pragma once
#include "ggl.h"
struct Vertex
{
	float Position[4];
	float Color[4];
	float Texcoord[4];
	float Normal[4];
};

class CVertexBuffer 
{
public:
	void SetSize(int vertexCount);
	inline int GetSize() { return m_vertex_count; }

	void SetPosition(int index, float x, float y, float z, float w = 1.0f);
	void SetColor(int index, float r, float g, float b, float a = 1.0);
	void SetTexcoord(int index, float x, float y);
	void SetNormal(int index, float x, float y, float z);
	void Bind();
	void Unbind();
	Vertex& Get(int index);
private:
	Vertex * m_vertexes;
	int m_vertex_count;
	GLuint m_vbo;

};