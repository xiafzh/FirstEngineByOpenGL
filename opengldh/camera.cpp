#include "camera.h"
#include "ggl_def.h"
#include "skybox.h"


CCamera::CCamera()
{
	m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_camera_pos = glm::vec3(50.0f, 50.0f, 50.0f);
	m_center_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
	m_sky_box = new CSkyBox();
}

void CCamera::Init()
{
	m_sky_box->Init("Res/skybox_t/");
}

void CCamera::SetMoveType(int type)
{
	m_move_type = type;
}

void CCamera::Move(float speed, glm::mat4& projectionMatrix)
{
	glm::vec3 move_vec;
	switch (m_move_type)
	{
	case EMT_FRONT:
		move_vec = glm::normalize(m_center_pos - m_camera_pos) * speed;
		break;
	case EMT_BACK:
		move_vec = glm::normalize(m_camera_pos - m_center_pos) * speed;
		break;
	case EMT_LEFT:
		move_vec = glm::normalize((m_camera_pos - m_center_pos)*m_world_up) * speed;
		break;
	case EMT_RIGHT:
		move_vec = glm::normalize((m_center_pos - m_camera_pos)*m_world_up) * speed;
		break;
	case EMT_INVALID:
	default:
		return;
	}
	printf("%f,%f,%f\n", move_vec.x, move_vec.y, move_vec.z);
	m_camera_pos += move_vec;
	m_sky_box->Draw(m_camera_pos, GetViewMatrix(), projectionMatrix);
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}

void CCamera::Rotate(int angle)
{
	m_camera_pos.y += angle;

	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}



