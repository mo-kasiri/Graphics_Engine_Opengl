#pragma once
#include <glm.hpp>
#include "glad.h"
class Camera
{
public:

	Camera();

	void Update();

	void Set3DView();

protected:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_upVector;
};

