#include "camera.h"
#include "ggl_def.h"
#include "skybox.h"


CCamera::CCamera()
{
	m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_camera_pos = glm::vec3(0.0f, 0.0f, 5.0f);
	m_center_pos = glm::vec3(0.0f, 0.0f, -1.0f);
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

void CCamera::Move(float speed)
{
	glm::vec3 move_vec = m_center_pos - m_camera_pos;
	switch (m_move_type)
	{
	case EMT_FRONT:
		move_vec = glm::normalize(move_vec) * speed;
		break;
	case EMT_BACK:
		move_vec = glm::normalize(move_vec) * -speed;
		break;
	case EMT_LEFT:
		move_vec = glm::normalize(VectorProd(move_vec, m_world_up)) * -speed;
		break;
	case EMT_RIGHT:
		move_vec = glm::normalize(VectorProd(move_vec, m_world_up)) * speed;
		break;
	case EMT_INVALID:
	default:
		return;
	}

	m_camera_pos += move_vec;
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}

void CCamera::Draw(glm::mat4& projectionMatrix)
{
	m_sky_box->Draw(m_camera_pos, GetViewMatrix(), projectionMatrix);
}

void CCamera::MouseMove(RECT& rect, int x, int y)
{

}

void CCamera::MouseWheel(short angle)
{
	float dis = 1.0f * angle / 120;

	glm::vec3 move_vec = glm::normalize(m_center_pos - m_camera_pos) * dis;

	glm::vec3 next_camera_pos = m_camera_pos + move_vec;
	glm::vec3 look_vec = m_center_pos - next_camera_pos;
	float k = CrossProd(look_vec, move_vec);
	float t = k / (glm::length(look_vec) * glm::length(move_vec));

	if (m_camera_pos + move_vec == m_center_pos) return;
	if (t * dis < 0) return;

	m_camera_pos = next_camera_pos;
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}

glm::vec3 CCamera::VectorProd(const glm::vec3& v1, const glm::vec3& v2)
{
	return glm::vec3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

float CCamera::CrossProd(const glm::vec3& v1, const glm::vec3& v2)
{
	return v1.x * v2.x + v1.y*v2.y + v1.z*v2.z;
}

