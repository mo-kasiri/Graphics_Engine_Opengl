#include <iostream>
#include "Input.h"
#include "Triangle.h"
#include "Shader.h"

Triangle::Triangle()
{
	this->m_position = glm::vec3(0.0f);

	this->m_translateMatrix = glm::mat4(1.0f);
	this->m_scaleMatrix = glm::mat4(1.0f);
	this->m_rotateMatrix = glm::mat4(1.0f);

	GLfloat vertices[] = {
			-0.1f, -0.1f, 0.0f,
			 0.1f, -0.1f, 0.0f,
			 0.0f,  0.1f, 0.0f
	};

	this->m_buffer.CreateBuffer(3);
	this->m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	this->m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);

	this->m_position = glm::vec3(0.0f);

}

Triangle::~Triangle()
{
	this->m_buffer.DestroyBuffer();
}

void Triangle::Render()
{
	Shader::Instance()->SendUniformData("translateMatrix", this->m_translateMatrix);
	Shader::Instance()->SendUniformData("scaleMatrix", this->m_scaleMatrix);
	Shader::Instance()->SendUniformData("rotateMatrix", this->m_rotateMatrix);

	this->m_buffer.Render(Buffer::TRIANGLES);
}

void Triangle::Update()
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
		if (Input::Instance()->GetKeyDown() == 'w')
		{
			this->m_position.z -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 's')
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
		std::cout << "x: " << this->m_position.x << " y: " << this->m_position.y << " z: " << this->m_position.z << std::endl;
		//this->m_modelMatrix = glm::mat4(1.0f);
		//this->m_modelMatrix = glm::translate(this->m_modelMatrix, m_position);
		this->Translate(m_position);
	}
}

void Triangle::Translate(const glm::vec3& pos)
{
	/*
	* // translation
	m_modelMatrix = [ x, y, z, 1];
	m_modelMatrix = [ x, y, z, 1] * [ 1, 0, 0, 0
									  0, 1, 0, 0			=> translate from [x,y,z] to [x+a, y+b, z+c]
									  0, 0, 1, 0
									  a, b, c, 1 ]
	*/
	this->m_translateMatrix = glm::mat4(1.0f);
	this->m_translateMatrix = glm::translate(this->m_translateMatrix, pos);
}

void Triangle::Scale(const glm::vec3& s)
{
	this->m_scaleMatrix = glm::scale(this->m_scaleMatrix, s);
}

void Triangle::Rotate(const glm::vec3& axis, const float& degree)
{
	this->m_rotateMatrix = glm::rotate(this->m_rotateMatrix, glm::radians(degree), axis);
}
