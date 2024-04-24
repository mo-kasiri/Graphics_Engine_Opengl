#pragma once
#include <glm.hpp>
#include <iostream>
#include "Buffer.h"
#include "Shader.h"
#include <gtc/matrix_transform.hpp>
#include "Input.h"

class Quad
{

public:
	Quad();
	~Quad();
	void Render();
	void Update();

	void Translate(const glm::vec3& pos);
	void Scale(const glm::vec3& s);
	void Rotate(const glm::vec3& axis, const float& degree);


private:
	Buffer m_buffer;
	//glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_translateMatrix;
	glm::mat4 m_scaleMatrix;
	glm::vec3 m_position;
};

