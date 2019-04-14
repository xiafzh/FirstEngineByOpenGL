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

	move_vec = glm::vec3(move_vec.x, 0, move_vec.z);
	m_camera_pos += move_vec;
	m_center_pos += move_vec;
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
}

void CCamera::Draw(glm::mat4& projectionMatrix)
{
	//m_sky_box->Draw(m_camera_pos, GetViewMatrix(), projectionMatrix);
}

void CCamera::MouseMove(glm::ivec4& rect, glm::ivec2& old, glm::ivec2& cur)
{
	printf("%d,%d,%d,%d\n", rect.x, rect.y, rect.z, rect.w);
	printf("%d,%d,%d,%d\n", old.x, old.y, cur.x, cur.y); 

	glm::vec3 look_vec = m_camera_pos - m_center_pos;
	float dist = glm::distance(m_camera_pos, m_center_pos);
	//rotate by x
	int delta_x = cur.x - old.x;
	float angle_x = atan(delta_x / dist);
	look_vec = glm::rotateX(look_vec, angle_x);

	//rotate by y
 	int delta_y = cur.y - old.y;
 	float angle_y = atan(delta_y / dist);
 	look_vec = glm::rotateY(look_vec, -angle_y);
 	
	m_camera_pos = m_center_pos + look_vec;
	m_viewMatrix = glm::lookAt(m_camera_pos, m_center_pos, m_world_up);
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

