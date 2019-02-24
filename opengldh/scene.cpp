#include "scene.h"
#include "ggl.h"
#include "utils.h"

const char* VS_PATH = "Res/test.vs";
const char* FS_PATH = "Res/test.fs";



CScene::CScene()
{

}

void CScene::Init() {
	float data[] = {
		-0.2f,-0.2f,-1.0f, 1.0f,0.0,0.0f,1.0f,
		0.2f,-0.2f,-1.0f, 0.0f,1.0f,0.0f,1.0f,
		0.0f,0.2f,-1.0f, 0.0f,0.0f,1.0f,1.0f,
		0.0f,0.4f,-1.0f, 0.0f,0.0f,1.0f,1.0f,
		-0.4f,0.4f,-1.0f, 0.0f,0.0f,1.0f,1.0f
	};
	m_program = CreateGPUProgram(VS_PATH, FS_PATH);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 7, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned short indexes[] = { 0,1,3,2 };
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 5, indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_positionLocation = glGetAttribLocation(m_program, "position");
	m_textureLocation = glGetAttribLocation(m_program, "texture");
	m_narmalLocation = glGetUniformLocation(m_program, "normal");

	m_modelMatrixLocation = glGetUniformLocation(m_program, "ModelMatrix");
	m_viewMatrixLocation = glGetUniformLocation(m_program, "ViewMatrix");
	m_projectionMatrixLocation = glGetUniformLocation(m_program, "ProjectionMatrix");
}
void CScene::SetViewPortSize(float width, float height) {
	m_projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 1000.0f);
}
void CScene::Draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_program);
	glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
	glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
	glUniformMatrix4fv(m_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(m_positionLocation);
	glVertexAttribPointer(m_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
// 	glEnableVertexAttribArray(5);
// 	glVertexAttribPointer(m_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
