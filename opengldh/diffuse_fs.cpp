#include "diffuse_fs.h"
#include "utils.h"
#include "shader.h"


CDiffuse::CDiffuse()
{

}

CDiffuse::~CDiffuse()
{

}

void CDiffuse::Init(const char*model_path)
{
	m_shader = new CShader();
	m_shader->Init("./Res/diffuse_vs.vs", "./Res/diffuse_vs.fs");


}

void CDiffuse::Draw(glm::mat4 & viewMatrix, glm::mat4 projectionMatrix)
{

}

void CDiffuse::SetPosition(float x, float y, float z)
{

}

void CDiffuse::SetTexture(const char*imagePath)
{

}
