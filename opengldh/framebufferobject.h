#pragma once

#include "ggl.h"

class CFrameBufferObject
{
public:
	CFrameBufferObject();
	CFrameBufferObject(int width, int height);
	~CFrameBufferObject();
public:
	inline GLuint GetFbo() const { return m_fbo; }
	inline GLuint GetColorBuffer() const { return m_color_buffer; }
	inline GLuint GetDepthBuffer() const { return m_depth_buffer; }

private:
	GLuint m_fbo;
	GLuint m_color_buffer;
	GLuint m_depth_buffer;
	GLuint m_stencil_buffer;

	int m_width;
	int m_height;
};
