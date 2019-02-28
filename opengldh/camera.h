#pragma once
#include "ggl.h"


class CCamera 
{
public:
	CCamera();

	void SetMoveType(int type);
	void Move(float speed);
	void Rotate(int angle);
	inline glm::mat4& GetViewMatrix() { return m_viewMatrix; }
private:
	int m_move_type;

	glm::vec3 m_camera_pos;
	glm::vec3 m_world_up;
	glm::vec3 m_center_pos;
	glm::mat4 m_viewMatrix;
};