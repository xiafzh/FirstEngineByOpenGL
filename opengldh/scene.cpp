#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "model.h"

const char* VS_PATH = "Res/test.vs";
const char* FS_PATH = "Res/test.fs";



CScene::CScene()
{
	m_model = new CModel();
}

void CScene::Init() 
{
	m_model->Init("Res/Sphere.obj");
	m_model->SetPosition(0.0f, 0.0f, -5.0f);
}
void CScene::SetViewPortSize(float width, float height) {
	m_projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 1000.0f);
}
void CScene::Draw() {
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_model->Draw(m_viewMatrix, m_projectionMatrix);
}
