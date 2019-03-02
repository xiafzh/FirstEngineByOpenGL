#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "model.h"
#include "ground.h"
#include "skybox.h"
#include "particlesystem.h"
#include "camera.h"

CScene::CScene()
{
	m_model = new CModel();
	m_ground = new CGround();
	//m_sky_box = new CSkyBox();
	m_particle = new CParticleSystem();
	m_camera = new CCamera();
}

void CScene::Init() 
{
	m_ground->Init();
	m_model->Init("Res/niutou.obj");
	m_model->SetTexture("Res/niutou.bmp");
	m_model->SetPosition(0.0f, 0.0f, -3.0f);
	//m_sky_box->Init("Res/skybox_t/");
	m_particle->Init(0.0f, 0.0f, 0.0f);
	m_camera->Init();
}

void CScene::SetViewPortSize(float width, float height) 
{
	m_projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void CScene::Draw() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_camera->Draw(m_projectionMatrix);
	//m_sky_box->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
	m_ground->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
	m_model->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
	m_particle->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
	m_camera->Move(1.0f);

}
