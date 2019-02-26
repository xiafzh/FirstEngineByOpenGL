#include "skybox.h"
#include "utils.h"

void CSkyBox::Init(const char *imageDir) 
{
	m_shader = new CShader[6];
	m_vertex_buffer = new CVertexBuffer[6];
	InitFront(imageDir);
	InitBack(imageDir);
	InitLeft(imageDir);
	InitRight(imageDir);
	InitTop(imageDir);
	InitBottom(imageDir);
}
void CSkyBox::InitFront(const char *imageDir) 
{
	m_shader[0].Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "front.bmp");
	m_shader[0].SetTexture("U_Texture", temp);
	m_vertex_buffer[0].SetSize(4);
	m_vertex_buffer[0].SetPosition(0, -0.5f, -0.5f, -0.5f);
	m_vertex_buffer[0].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[0].SetPosition(1, 0.5f, -0.5f, -0.5f);
	m_vertex_buffer[0].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[0].SetPosition(2, -0.5f, 0.5f, -0.5f);
	m_vertex_buffer[0].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[0].SetPosition(3, 0.5f, 0.5f, -0.5f);
	m_vertex_buffer[0].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitBack(const char *imageDir) 
{
	m_shader[1].Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "back.bmp");
	m_shader[1].SetTexture("U_Texture", temp);
	m_vertex_buffer[1].SetSize(4);
	m_vertex_buffer[1].SetPosition(0, 0.5f, -0.5f, 0.5f);
	m_vertex_buffer[1].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[1].SetPosition(1, -0.5f, -0.5f, 0.5f);
	m_vertex_buffer[1].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[1].SetPosition(2, 0.5f, 0.5f, 0.5f);
	m_vertex_buffer[1].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[1].SetPosition(3, -0.5f, 0.5f, 0.5f);
	m_vertex_buffer[1].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitLeft(const char *imageDir) 
{
	m_shader[2].Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "left.bmp");
	m_shader[2].SetTexture("U_Texture", temp);
	m_vertex_buffer[2].SetSize(4);
	m_vertex_buffer[2].SetPosition(0, -0.5f, -0.5f, 0.5f);
	m_vertex_buffer[2].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[2].SetPosition(1, -0.5f, -0.5f, -0.5f);
	m_vertex_buffer[2].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[2].SetPosition(2, -0.5f, 0.5f, 0.5f);
	m_vertex_buffer[2].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[2].SetPosition(3, -0.5f, 0.5f, -0.5f);
	m_vertex_buffer[2].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitRight(const char *imageDir) 
{
	m_shader[3].Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "right.bmp");
	m_shader[3].SetTexture("U_Texture", temp);
	m_vertex_buffer[3].SetSize(4);
	m_vertex_buffer[3].SetPosition(0, 0.5f, -0.5f, -0.5f);
	m_vertex_buffer[3].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[3].SetPosition(1, 0.5f, -0.5f, 0.5f);
	m_vertex_buffer[3].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[3].SetPosition(2, 0.5f, 0.5f, -0.5f);
	m_vertex_buffer[3].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[3].SetPosition(3, 0.5f, 0.5f, 0.5f);
	m_vertex_buffer[3].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitTop(const char *imageDir) 
{
	m_shader[4].Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "top.bmp");
	m_shader[4].SetTexture("U_Texture", temp);
	m_vertex_buffer[4].SetSize(4);
	m_vertex_buffer[4].SetPosition(0, -0.5f, 0.5f, -0.5f);
	m_vertex_buffer[4].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[4].SetPosition(1, 0.5f, 0.5f, -0.5f);
	m_vertex_buffer[4].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[4].SetPosition(2, -0.5f, 0.5f, 0.5f);
	m_vertex_buffer[4].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[4].SetPosition(3, 0.5f, 0.5f, 0.5f);
	m_vertex_buffer[4].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitBottom(const char *imageDir) {
	m_shader[5].Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, imageDir);
	strcat(temp, "bottom.bmp");
	m_shader[5].SetTexture("U_Texture", temp);
	m_vertex_buffer[5].SetSize(4);
	m_vertex_buffer[5].SetPosition(0, -0.5f, -0.5f, 0.5f);
	m_vertex_buffer[5].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[5].SetPosition(1, 0.5f, -0.5f, 0.5f);
	m_vertex_buffer[5].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[5].SetPosition(2, -0.5f, -0.5f, -0.5f);
	m_vertex_buffer[5].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[5].SetPosition(3, 0.5f, -0.5f, -0.5f);
	m_vertex_buffer[5].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::Draw(glm::mat4 &V, glm::mat4&P) 
{
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < 6; ++i) 
	{
		m_vertex_buffer[i].Bind();
		m_shader[i].Bind(glm::value_ptr(m_model_matrix), glm::value_ptr(V), glm::value_ptr(P));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_vertex_buffer[i].Unbind();
	}
}