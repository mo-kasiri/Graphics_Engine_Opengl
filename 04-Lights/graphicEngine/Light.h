#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Buffer.h"
class Light
{
public:
	Light();
	~Light();

	void Update();
	void Render();
	void SendToShader();
	void Translate(const glm::vec3& pos);
	void Scale(const glm::vec3& s);
	void Rotate(const glm::vec3& axis, const float& degree);

private:
	Buffer m_buffer;

	//glm::mat4 m_model;
	glm::vec3 m_position;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	glm::mat4 m_translateMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_rotateMatrix;
};

