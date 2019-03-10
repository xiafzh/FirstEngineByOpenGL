#include "model.h"
#include "utils.h"
#include "../vertexbuffer.h"
#include "../shader.h"

CModel::CModel()
{

}


void CModel::Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix)
{
	glEnable(GL_DEPTH_TEST);
	m_vertex_buffer->Bind();
	glm::mat4 it = glm::inverseTranspose(m_model_matrix);
	m_shader->Bind(glm::value_ptr(m_model_matrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader->GetProgram(), "IT_ModelMatrix"), 1, GL_FALSE, glm::value_ptr(it));

	glDrawArrays(GL_TRIANGLES, 0, m_vertex_buffer->GetSize());
	m_vertex_buffer->Unbind();
	
}

void CModel::SetPosition(float x, float y, float z)
{
	m_model_matrix = glm::translate(x, y, z)*glm::scale(0.01f, 0.01f, 0.01f)
		*glm::rotate(-90.0f, 0.0f, 1.0f, 0.0f);
}

void CModel::SetTexture(const char*imagePath)
{
	m_shader->SetTexture("U_Texture", imagePath);
}
