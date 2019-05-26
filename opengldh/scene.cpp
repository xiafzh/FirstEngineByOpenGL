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
#include "diffuse_fs.h"
#include "model/model_obj_ext.h"

CScene::CScene()
{
// 	m_ground = new CGround();
// 	m_particle = new CParticleSystem();
	m_camera = new CCamera();
//	m_model = new CModelObj();
	m_model = new CModelObjExt();
// 	m_fbx_model = new CModelFbx();
	//m_diffuse = new CDiffuse();
}

void CScene::Init() 
{
	//m_diffuse->Init("Res/Sphere.objm");
// 	m_ground->Init();
 	m_model->Init("Res/Sphere.objm");
 //	m_model->SetTexture("Res/niutou.bmp");
 	m_model->SetPosition(0.0f, 0.0f, -3.0f);

// 	m_fbx_model->Init("Res/dashu.FBX");
// 	m_fbx_model->SetPosition(0.0f, 0.0f, -3.0f);

// 	m_particle->Init(0.0f, 0.0f, 0.0f);
 	m_camera->Init();
}

void CScene::SetViewPortSize(float width, float height) 
{
	m_width = width;
	m_height = height;
	m_projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
	//if (nullptr != m_fbo)
	//	delete m_fbo;
	//m_fbo = new CFrameBufferObject(m_width, m_height);
}

void CScene::Draw() 
{
 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	m_camera->Draw(m_projectionMatrix);
 	//m_ground->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
 //	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo->GetFbo());
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
 	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	m_model->Draw(m_camera->GetViewMatrix(), m_projectionMatrix, nullptr);
 
	
	//m_fbx_model->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
 	//m_particle->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
	//m_camera->Move(1.0f);

	//m_diffuse->Draw(m_camera->GetViewMatrix(), m_projectionMatrix);
}
