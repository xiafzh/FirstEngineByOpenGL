#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "model.h"
#include "ground.h"
#include "skybox.h"

const char* VS_PATH = "Res/test.vs";
const char* FS_PATH = "Res/test.fs";

CScene::CScene()
{
	m_model = new CModel();
	m_ground = new CGround();
	m_sky_box = new CSkyBox();
}

void CScene::Init() 
{
	m_ground->Init();
	m_model->Init("Res/Sphere.obj");
	m_model->SetTexture("Res/earth.bmp");
	m_model->SetPosition(0.0f, 0.0f, -5.0f);
	m_sky_box->Init("Res/");
}

void CScene::SetViewPortSize(float width, float height) 
{
	m_projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
}

void CScene::Draw() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_sky_box->Draw(m_viewMatrix, m_projectionMatrix);
	m_ground->Draw(m_viewMatrix, m_projectionMatrix);
	m_model->Draw(m_viewMatrix, m_projectionMatrix);
}
