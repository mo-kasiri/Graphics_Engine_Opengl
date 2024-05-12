#include <iostream>
#include "Light.h"
#include "Shader.h"
#include "Input.h"
Light::Light()
{

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f, 1.0f, 0.0f);

	GLfloat vertices[] = { 0.0f, 0.0f, 0.0f };
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f };

	this->m_translateMatrix = glm::mat4(1.0f);
	this->m_scaleMatrix = glm::mat4(1.0f);
	this->m_rotateMatrix = glm::mat4(1.0f);

	this->m_buffer.CreateBuffer(1);

	this->m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	this->m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);

	this->m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	this->m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);
	glPointSize(10.0f);
}

Light::~Light()
{
	this->m_buffer.DestroyBuffer();
}

void Light::Update()
{
	if (Input::Instance()->IsKeyPressed())
	{
		if (Input::Instance()->GetKeyDown() == 'j')
		{
			this->m_position.x -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'l')
		{
			this->m_position.x += 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'i')
		{
			this->m_position.z -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'k')
		{
			this->m_position.z += 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'u')
		{
			this->m_position.y -= 0.001f;
		}
		if (Input::Instance()->GetKeyDown() == 'o')
		{
			this->m_position.y += 0.001f;
		}
		std::cout << "x: " << this->m_position.x << " y: " << this->m_position.y << " z: " << this->m_position.z << std::endl;
		//this->m_modelMatrix = glm::mat4(1.0f);
		//this->m_modelMatrix = glm::translate(this->m_modelMatrix, m_position);
		this->Translate(m_position);
	}
}

void Light::Render()
{
	//Shader::Instance()->SendUniformData("model", this->m_model);
	Shader::Instance()->SendUniformData("translateMatrix", this->m_translateMatrix);
	Shader::Instance()->SendUniformData("scaleMatrix", this->m_scaleMatrix);
	Shader::Instance()->SendUniformData("rotateMatrix", this->m_rotateMatrix);
	Shader::Instance()->SendUniformData("isLit", false);
	Shader::Instance()->SendUniformData("isTextured", false);

	
	this->m_buffer.Render(Buffer::POINTS);
}

void Light::SendToShader()
{
	Shader::Instance()->SendUniformData("light.ambient", this->m_ambient.r, this->m_ambient.g, this->m_ambient.b);
	Shader::Instance()->SendUniformData("light.diffuse", this->m_diffuse.r, this->m_diffuse.g, this->m_diffuse.b);
	Shader::Instance()->SendUniformData("light.specular", this->m_specular.r, this->m_specular.g, this->m_specular.b);
	Shader::Instance()->SendUniformData("light.position", this->m_position.r, this->m_position.g, this->m_position.b);
}

void Light::Translate(const glm::vec3& pos)
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

void Light::Scale(const glm::vec3& s)
{
	this->m_scaleMatrix = glm::scale(this->m_scaleMatrix, s);
}

void Light::Rotate(const glm::vec3& axis, const float& degree)
{
	this->m_rotateMatrix = glm::rotate(this->m_rotateMatrix, glm::radians(degree), axis);
}
