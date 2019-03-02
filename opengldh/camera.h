#pragma once
#include "ggl.h"

class CSkyBox;
class CCamera 
{
public:
	CCamera();

	void Init();
	void SetMoveType(int type);
	void Move(float speed);
	void Draw(glm::mat4& projectionMatrix);
	void Rotate(int angle);
	glm::vec3 VectorProd(const glm::vec3& v1, const glm::vec3& v2);
	inline glm::mat4& GetViewMatrix() { return m_viewMatrix; }
private:
	int m_move_type;

	CSkyBox* m_sky_box;

	glm::vec3 m_camera_pos;
	glm::vec3 m_world_up;
	glm::vec3 m_center_pos;
	glm::mat4 m_viewMatrix;
};