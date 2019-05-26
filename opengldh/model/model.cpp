#include "model.h"
#include "utils.h"
#include "../vertexbuffer.h"
#include "../shader.h"
#include "../framebufferobject.h"

CModel::CModel()
{

}


CModel::~CModel()
{
	if (NULL != m_shader)
	{
		delete m_shader;
		m_shader = nullptr;
	}

	for (auto iter = m_vertex_buffers.begin(); iter != m_vertex_buffers.end(); ++iter)
	{
		delete (*iter);
	}
}

void CModel::Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix, CFrameBufferObject* fbo /*=nullptr*/)
{
	glEnable(GL_DEPTH_TEST);
	for (auto iter = m_vertex_buffers.begin(); iter != m_vertex_buffers.end(); ++iter)
	{
		(*iter)->Bind();
		glm::mat4 it = glm::inverseTranspose(m_model_matrix);
		m_shader->Bind(glm::value_ptr(m_model_matrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), fbo);

		GLint local_nm = glGetUniformLocation(m_shader->GetProgram(), "IT_ModelMatrix");
		glUniformMatrix4fv(local_nm, 1, GL_FALSE, glm::value_ptr(it));

		glDrawArrays(GL_TRIANGLES, 0, (*iter)->GetSize());
		(*iter)->Unbind();
	}
	
}

void CModel::SetPosition(float x, float y, float z)
{
	m_model_matrix = glm::translate(x, y, z);// *glm::scale(0.01f, 0.01f, 0.01f)*glm::rotate(-90.0f, 0.0f, 1.0f, 0.0f);
}

void CModel::SetTexture(const char*imagePath)
{
	m_shader->SetTexture("U_Texture", imagePath);
}
