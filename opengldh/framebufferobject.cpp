#include "framebufferobject.h"

CFrameBufferObject::CFrameBufferObject()
	: m_color_buffer(0)
	, m_depth_buffer(0)
	, m_stencil_buffer(0)
	, m_width(0)
	, m_height(0)
	, m_fbo(0)
{
	
	
}

CFrameBufferObject::CFrameBufferObject(int width, int height)
	: m_color_buffer(0)
	, m_depth_buffer(0)
	, m_stencil_buffer(0)
	, m_width(width)
	, m_height(height)
	, m_fbo(0)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// color buffer
	glGenTextures(1, &m_color_buffer);
	glBindTexture(GL_TEXTURE_2D, m_color_buffer);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_buffer, 0);

	// depth buffer
	glGenTextures(1, &m_depth_buffer);
	glBindTexture(GL_TEXTURE_2D, m_depth_buffer);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr); 
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_TEXTURE_2D, m_depth_buffer, 0);

	// stencil buffer
	//TODO::

	GLenum st = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (GL_FRAMEBUFFER_COMPLETE != st)
	{
		std::cout << "Create FBO failed" << std::endl;
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

CFrameBufferObject::~CFrameBufferObject()
{

}

