#include "shader.h"
#include "utils.h"
#include "vertexbuffer.h"
#include "framebufferobject.h"

void CShader::Init(const char*vs, const char*fs) 
{
	int file_size = 0;
	const char* vs_code = (char*)LoadFileContent(vs, file_size);
	const char* fs_code = (char*)LoadFileContent(fs, file_size);
	GLuint vs_shader = CompileShader(GL_VERTEX_SHADER, vs_code);
	if (vs_shader==0)
	{
		return;
	}
	GLuint fs_shader = CompileShader(GL_FRAGMENT_SHADER, fs_code);
	if (fs_shader == 0) 
	{
		return;
	}
	m_program=CreateProgram(vs_shader, fs_shader);
	glDeleteShader(vs_shader);
	glDeleteShader(fs_shader);
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

void CShader::Bind(float *M, float *V, float*P, CFrameBufferObject* fbo/* = nullptr*/)
{
	glUseProgram(m_program);
	glUniformMatrix4fv(m_model_matrix_location, 1, GL_FALSE, M);
	glUniformMatrix4fv(m_view_matrix_location, 1, GL_FALSE, V);
	glUniformMatrix4fv(m_projection_matrix_location, 1, GL_FALSE, P);
	int index = 0;
	for (auto iter = m_uniform_textures.begin(); iter != m_uniform_textures.end(); ++iter) 
	{
		glActiveTexture(GL_TEXTURE0 + index);
		if (nullptr == fbo)
		{
			glBindTexture(GL_TEXTURE_2D, iter->second->m_texture);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, fbo->GetColorBuffer());
		}
		glUniform1i(iter->second->m_location, index++);
	}
	for (auto iter = m_uniform_vec4s.begin(); iter != m_uniform_vec4s.end(); ++iter)
	{
		glUniform4fv(iter->second->m_location, 1, iter->second->v);
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

void CShader::SetTexture(const char * name, GLuint texture)
{
	auto iter = m_uniform_textures.find(name);
	if (iter == m_uniform_textures.end()) 
	{
		GLint location = glGetUniformLocation(m_program, name);
		if (location != -1) 
		{
			UniformTexture*t = new UniformTexture;
			t->m_location = location;
			t->m_texture = texture;
			m_uniform_textures.insert(std::pair<std::string, UniformTexture*>(name, t));
		}
	}
	else 
	{
		glDeleteTextures(1, &iter->second->m_texture);
		iter->second->m_texture = texture;
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

void CShader::SetNM(glm::mat4& model)
{
	GLint glnm = glGetUniformLocation(m_program, "NM");
	if (glnm >= 0)
	{
		glm::mat4 nm = glm::inverseTranspose(model);
		glUniformMatrix4fv(glnm, 1, GL_FALSE, glm::value_ptr(nm));
	}
}
