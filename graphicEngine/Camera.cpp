#include "Camera.h"
#include "Shader.h"
#include <gtc\matrix_transform.hpp>
#include "Input.h"
Camera::Camera()
{
	this->m_viewMatrix = glm::mat4(1.0f);
	this->m_projectionMatrix = glm::mat4(1.0f);
	

	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::Update()
{
	if (Input::Instance()->IsKeyPressed())
	{
		if (Input::Instance()->GetKeyDown() == 'a')
		{
			this->m_position.x -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'd')
		{
			this->m_position.x += 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 's')
		{
			this->m_position.z -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'w')
		{
			this->m_position.z += 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'q')
		{
			this->m_position.y -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'e')
		{
			this->m_position.y += 0.001f;
		}
	}

	Shader::Instance()->SendUniformData("viewMatrix", this->m_viewMatrix);
	this->m_viewMatrix = glm::lookAt(this->m_position, this->m_position + this->m_direction, this->m_upVector);
}

void Camera::Set3DView()
{
	GLfloat FOV = 45.0f;
	GLfloat aspectRatio = 1280.f / 720.f;

	this-> m_projectionMatrix = glm::perspective(FOV, aspectRatio, 0.001f, 1000.0f);
	Shader::Instance()->SendUniformData("projectionMatrix", this->m_projectionMatrix);

}
