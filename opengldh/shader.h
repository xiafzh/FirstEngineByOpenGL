#pragma once
#include "ggl.h"
struct UniformTexture
{
	GLint m_location;
	GLuint m_texture;
	UniformTexture() 
	{
		m_location = -1;
		m_texture = 0;
	}
};

struct SUniformVector4f 
{
	GLint m_location;
	float v[4];
	SUniformVector4f() 
	{
		m_location = -1;
		memset(v, 0, sizeof(float) * 4);
	}
};
class CFrameBufferObject;

class CShader 
{
public:
	void Init(const char*vs, const char*fs);
	void Bind(float *M, float *V, float*P, CFrameBufferObject* fbo = nullptr);
	void SetTexture(const char * name, const char*imagePath);
	void SetTexture(const char * name, GLuint texture);
	void SetVec4(const char * name, float x, float y, float z, float w);
public:
	inline GLuint GetProgram() const { return m_program; }
private:
	GLuint m_program;
	std::map<std::string, UniformTexture*> m_uniform_textures;
	std::map<std::string, SUniformVector4f*> m_uniform_vec4s;

	GLint m_model_matrix_location;
	GLint m_view_matrix_location;
	GLint m_projection_matrix_location;
	GLint m_position_location;
	GLint m_color_location;
	GLint m_texcoord_location;
	GLint m_normal_location;
};