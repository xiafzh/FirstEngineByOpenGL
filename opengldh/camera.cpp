#include "camera.h"


CCamera::CCamera()
{
	m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void CCamera::Init(float x, float y, float z)
{
	m_camera_pos = glm::vec3(x, y, z);
}

void CCamera::Move(int len)
{
	//	m_camera_pos += move_vec;
	m_viewMatrix = glm::lookAt(m_camera_pos, glm::vec3(1.0f, 1.0f, 1.0f), m_world_up);
}

void CCamera::Rotate(int angle)
{

	m_viewMatrix = glm::lookAt(m_camera_pos, glm::vec3(1.0f, 1.0f, 1.0f), m_world_up);
}



