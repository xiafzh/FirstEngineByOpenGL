#include "shader.h"
#include "utils.h"
#include "vertexbuffer.h"

void CShader::Init(const char*vs, const char*fs) 
{
	int nFileSize = 0;
	const char*vsCode = (char*)LoadFileContent(vs,nFileSize);
	const char*fsCode = (char*)LoadFileContent(fs,nFileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsCode);
	if (vsShader==0)
	{
		return;
	}
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsCode);
	if (fsShader == 0) 
	{
		return;
	}
	m_program=CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	if (m_program != 0)
	{
		m_model_matrix_location = glGetUniformLocation(m_program, "ModelMatrix");
		m_view_matrix_location = glGetUniformLocation(m_program, "ViewMatrix");
		m_projection_matrix_location = glGetUniformLocation(m_program, "ProjectionMatrix");
		m_position_location = glGetAttribLocation(m_program, "position");
		m_color_location = glGetAttribLocation(m_program, "color");
		m_texcoord_location = glGetAttribLocation(m_program, "texcoord");
		m_normal_location = glGetAttribLocation(m_program, "normal");
	}
}

void CShader::Bind(float *M, float *V, float*P) 
{
	glUseProgram(m_program);
	glUniformMatrix4fv(m_model_matrix_location, 1, GL_FALSE, M);
	glUniformMatrix4fv(m_view_matrix_location, 1, GL_FALSE, V);
	glUniformMatrix4fv(m_projection_matrix_location, 1, GL_FALSE, P);
	int index = 0;
	for (auto iter = m_uniform_textures.begin(); iter != m_uniform_textures.end(); ++iter) 
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, iter->second->m_texture);
		glUniform1i(iter->second->m_location, index++);
	}
	glEnableVertexAttribArray(m_position_location);
	glVertexAttribPointer(m_position_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(m_color_location);
	glVertexAttribPointer(m_color_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(m_texcoord_location);
	glVertexAttribPointer(m_texcoord_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(m_normal_location);
	glVertexAttribPointer(m_normal_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 12));
}
void CShader::SetTexture(const char * name, const char*imagePath)
{
	auto iter = m_uniform_textures.find(name);
	if (iter == m_uniform_textures.end())
	{
		GLint location = glGetUniformLocation(m_program, name);
		if (location != -1)
		{
			UniformTexture*t = new UniformTexture;
			t->m_location = location;
			t->m_texture = CreateTexture2DFromBMP(imagePath);
			m_uniform_textures.insert(std::pair<std::string, UniformTexture*>(name, t));
		}
	}
	else
	{
		glDeleteTextures(1, &iter->second->m_texture);
		iter->second->m_texture = CreateTexture2DFromBMP(imagePath);
	}
}

void CShader::SetVec4(const char * name, float x, float y, float z, float w) 
{
	auto iter = m_uniform_vec4s.find(name);
	if (iter == m_uniform_vec4s.end()) 
	{
		GLint location = glGetUniformLocation(m_program, name);
		if (location != -1) 
		{
			SUniformVector4f* v = new SUniformVector4f();
			v->v[0] = x;
			v->v[1] = y;
			v->v[2] = z;
			v->v[3] = w;
			v->m_location = location;
			m_uniform_vec4s.insert(std::pair<std::string, SUniformVector4f*>(name, v));
		}
	}
	else 
	{
		iter->second->v[0] = x;
		iter->second->v[1] = y;
		iter->second->v[2] = z;
		iter->second->v[3] = w;
	}
}
