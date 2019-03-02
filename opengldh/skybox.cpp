#include "skybox.h"
#include "utils.h"


void CSkyBox::Init(const char *imageDir) 
{
	m_camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_shader = new CShader[6];
	m_vertex_buffer = new CVertexBuffer[6];
	InitTexture(m_shader[0], imageDir, "front.bmp");
	InitTexture(m_shader[1], imageDir, "back.bmp");
	InitTexture(m_shader[2], imageDir, "left.bmp");
	InitTexture(m_shader[3], imageDir, "right.bmp");
	InitTexture(m_shader[4], imageDir, "top.bmp");
	InitTexture(m_shader[5], imageDir, "bottom.bmp");
}

void CSkyBox::InitTexture(CShader& shader, const char* dir, const char* name)
{
	if (nullptr == dir || nullptr == name) return;

	shader.Init("Res/skybox.vs", "Res/skybox.fs");
	char temp[256];
	memset(temp, 0, 256);
	strcpy(temp, dir);
	strcat(temp, name);
	shader.SetTexture("U_Texture", temp);
}

void CSkyBox::InitFront() 
{
	m_vertex_buffer[0].SetSize(4);
	m_vertex_buffer[0].SetPosition(0, m_camera_pos.x - 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[0].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[0].SetPosition(1, m_camera_pos.x + 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[0].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[0].SetPosition(2, m_camera_pos.x - 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[0].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[0].SetPosition(3, m_camera_pos.x + 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[0].SetTexcoord(3, 1.0f, 1.0f);
}

void CSkyBox::InitBack() 
{
	m_vertex_buffer[1].SetSize(4);
	m_vertex_buffer[1].SetPosition(0, m_camera_pos.x + 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[1].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[1].SetPosition(1, m_camera_pos.x - 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[1].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[1].SetPosition(2, m_camera_pos.x + 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[1].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[1].SetPosition(3, m_camera_pos.x - 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[1].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitLeft() 
{
	m_vertex_buffer[2].SetSize(4);
	m_vertex_buffer[2].SetPosition(0, m_camera_pos.x - 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[2].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[2].SetPosition(1, m_camera_pos.x - 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[2].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[2].SetPosition(2, m_camera_pos.x - 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[2].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[2].SetPosition(3, m_camera_pos.x - 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[2].SetTexcoord(3, 1.0f, 1.0f);
}
void CSkyBox::InitRight() 
{
	m_vertex_buffer[3].SetSize(4);
	m_vertex_buffer[3].SetPosition(0, m_camera_pos.x + 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[3].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[3].SetPosition(1, m_camera_pos.x + 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[3].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[3].SetPosition(2, m_camera_pos.x + 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[3].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[3].SetPosition(3, m_camera_pos.x + 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[3].SetTexcoord(3, 1.0f, 1.0f);
}

void CSkyBox::InitTop() 
{
	m_vertex_buffer[4].SetSize(4);
	m_vertex_buffer[4].SetPosition(0, m_camera_pos.x - 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[4].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[4].SetPosition(1, m_camera_pos.x + 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[4].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[4].SetPosition(2, m_camera_pos.x - 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[4].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[4].SetPosition(3, m_camera_pos.x + 0.5f, m_camera_pos.y + 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[4].SetTexcoord(3, 1.0f, 1.0f);
}

void CSkyBox::InitBottom()
{

	m_vertex_buffer[5].SetSize(4);
	m_vertex_buffer[5].SetPosition(0, m_camera_pos.x - 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[5].SetTexcoord(0, 0.0f, 0.0f);
	m_vertex_buffer[5].SetPosition(1, m_camera_pos.x + 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z + 0.5f);
	m_vertex_buffer[5].SetTexcoord(1, 1.0f, 0.0f);
	m_vertex_buffer[5].SetPosition(2, m_camera_pos.x - 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[5].SetTexcoord(2, 0.0f, 1.0f);
	m_vertex_buffer[5].SetPosition(3, m_camera_pos.x + 0.5f, m_camera_pos.y - 0.5f, m_camera_pos.z - 0.5f);
	m_vertex_buffer[5].SetTexcoord(3, 1.0f, 1.0f);
}

void CSkyBox::Draw(glm::vec3& camera_pos, glm::mat4 &V, glm::mat4&P) 
{
	m_camera_pos = camera_pos;

	InitFront();
	InitBack();
	InitLeft();
	InitRight();
	InitTop();
	InitBottom();

	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < 6; ++i) 
	{
		m_vertex_buffer[i].Bind();
		m_shader[i].Bind(glm::value_ptr(m_model_matrix), glm::value_ptr(V), glm::value_ptr(P));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_vertex_buffer[i].Unbind();
	}
}