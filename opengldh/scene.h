#pragma once
#include "ggl.h"

class CModel;
class CGround;
class CSkyBox;
class CParticleSystem;
class CCamera;
class CScene
{
public:
	CScene();

	void Init();
	void SetViewPortSize(float width, float height);
	void Draw();
public:
	inline CCamera* GetCamera() const { return m_camera; }
private:
	GLuint m_vbo;
	GLuint m_ebo;

	GLuint m_program;
	
	GLint m_positionLocation;
	GLint m_textureLocation;
	GLint m_narmalLocation;
	
	GLint m_modelMatrixLocation;
	GLint m_viewMatrixLocation;
	GLint m_projectionMatrixLocation;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_projectionMatrix;

	CModel* m_model;
	CGround* m_ground;
	CParticleSystem* m_particle;
	CCamera* m_camera;
};
