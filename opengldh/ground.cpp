#include "ground.h"
#include "vertexbuffer.h"
#include "shader.h"

CGround::CGround()
{

}

void CGround::Init() 
{
	m_vertex_buffer = new CVertexBuffer();
	
	m_vertex_buffer->SetSize(1600);
	for (int z = 0; z < 20; ++z) 
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; ++x) 
		{
			int offset = (x + z * 20) * 4;
			float xStart = x * 10.0f - 100.0f;
			m_vertex_buffer->SetPosition(offset, xStart, -1.0f, zStart);
			m_vertex_buffer->SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
			m_vertex_buffer->SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
			m_vertex_buffer->SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);
			m_vertex_buffer->SetNormal(offset, 0.0f, 1.0f, 0.0f);
			m_vertex_buffer->SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
			m_vertex_buffer->SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
			m_vertex_buffer->SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);
			if ((z % 2) ^ (x % 2)) 
			{
				m_vertex_buffer->SetColor(offset, 0.1f, 0.1f, 0.1f);
				m_vertex_buffer->SetColor(offset + 1, 0.1f, 0.1f, 0.1f);
				m_vertex_buffer->SetColor(offset + 2, 0.1f, 0.1f, 0.1f);
				m_vertex_buffer->SetColor(offset + 3, 0.1f, 0.1f, 0.1f);
			}
			else {
				m_vertex_buffer->SetColor(offset, 0.8f, 0.8f, 0.8f);
				m_vertex_buffer->SetColor(offset + 1, 0.8f, 0.8f, 0.8f);
				m_vertex_buffer->SetColor(offset + 2, 0.8f, 0.8f, 0.8f);
				m_vertex_buffer->SetColor(offset + 3, 0.8f, 0.8f, 0.8f);
			}
		}
	}
	m_shader = new Shader;
	m_shader->Init("Res/ground.vs", "Res/ground.fs");
}
void CGround::Draw(glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix) 
{
	glEnable(GL_DEPTH_TEST);
	m_vertex_buffer->Bind();
	m_shader->Bind(glm::value_ptr(m_model_matrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	for (int i = 0; i < 400; i++) 
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	m_vertex_buffer->Unbind();
}