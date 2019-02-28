#pragma once
#include "ggl.h"


class CCamera 
{
public:
	CCamera();
	void Init(float x, float y, float z);

	void Move(int len);
	void Rotate(int angle);
	inline glm::mat4& GetViewMatrix() { return m_viewMatrix; }
private:
	glm::vec3 m_camera_pos;
	glm::vec3 m_world_up;
	glm::mat4 m_viewMatrix;
};