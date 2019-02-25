#include "vertexbuffer.h"
#include "utils.h"
void CVertexBuffer::SetSize(int vertexCount) 
{
	m_vertex_count = vertexCount;
	m_vertexes = new Vertex[m_vertex_count];
	memset(m_vertexes, 0, sizeof(Vertex)*m_vertex_count);
	m_vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertex_count, GL_STATIC_DRAW, nullptr);
}

void CVertexBuffer::SetPosition(int index, float x, float y, float z, float w) 
{
	m_vertexes[index].Position[0] = x;
	m_vertexes[index].Position[1] = y;
	m_vertexes[index].Position[2] = z;
	m_vertexes[index].Position[3] = w;
}

void CVertexBuffer::SetColor(int index, float r, float g, float b, float a) 
{
	m_vertexes[index].Color[0] = r;
	m_vertexes[index].Color[1] = g;
	m_vertexes[index].Color[2] = b;
	m_vertexes[index].Color[3] = a;
}

void CVertexBuffer::SetTexcoord(int index, float x, float y) 
{
	m_vertexes[index].Texcoord[0] = x;
	m_vertexes[index].Texcoord[1] = y;
}
void CVertexBuffer::SetNormal(int index, float x, float y, float z) 
{
	m_vertexes[index].Normal[0] = x;
	m_vertexes[index].Normal[1] = y;
	m_vertexes[index].Normal[2] = z;
	m_vertexes[index].Normal[3] = 1.0;
}

void CVertexBuffer::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*m_vertex_count, m_vertexes);
}

void CVertexBuffer::Unbind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vertex&CVertexBuffer::Get(int index) 
{
	return m_vertexes[index];
}