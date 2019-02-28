#include "particlesystem.h"
#include "utils.h"

CParticleSystem::CParticleSystem()
{

}

void CParticleSystem::Init(float x, float y, float z) 
{
	m_model_matrix = glm::translate(x, y, z);
	m_vertex_buffer = new CVertexBuffer;
	int particleCount = 180;
	m_vertex_buffer->SetSize(particleCount);
	for (int i = 0; i < particleCount; ++i) {
		m_vertex_buffer->SetPosition(i, 2.0f*cosf(float(i) * 8.0f*3.14f / 180.0f), 0.0f, 2.0f*sinf(float(i) * 8.0f*3.14f / 180.0f));
		m_vertex_buffer->SetColor(i, 0.1f, 0.4f, 0.6f);
	}
	m_shader = new CShader;
	m_shader->Init("Res/particle.vs", "Res/particle.fs");
	m_shader->SetTexture("U_Texture", CreateProcedureTexture(128));
}
void CParticleSystem::Draw(glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix) 
{
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	m_vertex_buffer->Bind();
	m_shader->Bind(glm::value_ptr(m_model_matrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	glDrawArrays(GL_POINTS, 0, m_vertex_buffer->GetSize());
	m_vertex_buffer->Unbind();
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_PROGRAM_POINT_SIZE);
}