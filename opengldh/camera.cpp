#include "camera.h"
#include "ggl_def.h"


CCamera::CCamera()
{
	m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_camera_pos = glm::vec3(0.0f, 0.0f, 1.0f);
	m_center_pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void CCamera::SetMoveType(int type)
{
	m_move_type = type;
}

void CCamera::Move(float speed)
{
	glm::vec3 move_vec;
	switch (m_move_type)
	{
	case EMT_FRONT:
		move_vec = glm::vec3(0.0f, 0.0f, -1.0f * speed);
		break;
	case EMT_BACK:
		move_vec = glm::vec3(0.0f, 0.0f, 1.0f * speed);
		break;
	case EMT_LEFT:
	case EMT_RIGHT:
	case EMT_INVALID:
	default:
		return;
	}

	m_camera_pos += move_vec;
	m_center_pos += move_vec;
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}

void CCamera::Rotate(int angle)
{
	m_camera_pos.y += angle;

	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}



