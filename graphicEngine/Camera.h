#pragma once
#include <glm.hpp>
#include "glad.h"
class Camera
{
public:

	Camera();

	void Update();

protected:
	glm::mat4 m_viewMatrix;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_upVector;
};

