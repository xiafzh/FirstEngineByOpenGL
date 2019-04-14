#include "scene.h"
#include "ggl.h"
#include "utils.h"
#include "ground.h"
#include "skybox.h"
#include "particlesystem.h"
#include "camera.h"
#include "model/model_obj.h"
#include "model/model_fbx.h"
#include "framebufferobject.h"

CScene::CScene()
{
	m_ground = new CGround();
	m_particle = new CParticleSystem();
	m_camera = new CCamera();
	m_model = new CModelObj();
	m_fbx_model = new CModelFbx();
}

void CScene::Init() 
{
	m_ground->Init();
 	m_model->Init("Res/niutou.objm");
	m_model->SetTexture("Res/niutou.bmp");
	m_model->SetPosition(0.0f, 0.0f, -3.0f);

// 	m_fbx_model->Init("Res/dashu.FBX");
// 	m_fbx_model->SetPosition(0.0f, 0.0f, -3.0f);

	m_particle->Init(0.0f, 0.0f, 0.0f);
	m_camera->Init();
}

void CScene::SetViewPortSize(float width, float height) 
{
	m_width = width;
	m_height = height;
	m_projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
	if (nullptr != m_fbo)
		delete m_fbo;
	m_fbo = new CFrameBufferObject(m_width, m_height);
}

void CScene::Draw() 
{
 	glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	m_camera->Draw(m_projectionMatrix);
 	//m_ground->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
 	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo->GetFbo());
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	m_model->Draw(m_camera->GetViewMatrix(), m_projectionMatrix, nullptr);
 	glBindFramebuffer(GL_FRAMEBUFFER, 0);
 	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_fbo->GetColorBuffer());

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -4.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -4.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -4.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -4.0f);
	glEnd();
	glFlush();
	
	//m_fbx_model->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
 	//m_particle->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
	//m_camera->Move(1.0f);

}
