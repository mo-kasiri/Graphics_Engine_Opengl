#include "Quad.h"


Quad::Quad()
{
	
	//this->m_modelMatrix = glm::mat4(1.0f); // Identity matrix
	this->m_position = glm::vec3(0.0f);

	
	this->m_translateMatrix = glm::mat4(1.0f);
	this->m_scaleMatrix = glm::mat4(1.0f);
	this->m_rotateMatrix = glm::mat4(1.0f);



	GLfloat vertices[] =  {-0.5f, 0.5f, 0.0f,
							0.5f, 0.5f, 0.0f,
						   -0.5f,-0.5f, 0.0f, // triangle 1

						   -0.5f,-0.5f, 0.0f, // triangle 2
							0.5f, 0.5f, 0.0f,
							0.5f,-0.5f, 0.0f };

	// data that represents color for quad
	GLfloat colors[] = { 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,

						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f };

	GLfloat UVs[] = { 0.0f, 1.0f,
					  1.0f, 1.0f,
					  0.0f, 0.0f, // triangle 1

					  0.0f, 0.0f, // triangle 2
					  1.0f, 1.0f,
					  1.0f, 0.0f };

	
	// creating, filling and linking shaders
	this->m_buffer.CreateBuffer(6);
	this->m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	this->m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);
	this->m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::SINGLE);

	this->m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	this->m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);
	this->m_buffer.LinkBuffer("textureIn", Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);

	this->m_texture.Load("Textures/crate.png");

	this->m_shininess = 50.0f;
	this->m_position = glm::vec3(0.0f);
	this->m_ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	this->m_diffuse = glm::vec3(0.1f, 0.7f, 0.2f);
	this->m_specular = glm::vec3(0.8f, 0.8f, 0.8f);


}

Quad::~Quad()
{
	this->m_buffer.DestroyBuffer();
}



void Quad::Render()
{
	Shader::Instance()->SendUniformData("isLit", true);
	Shader::Instance()->SendUniformData("isTextured", true);
	//Shader::Instance()->SendUniformData("modelMatrix", this->m_modelMatrix);
	Shader::Instance()->SendUniformData("translateMatrix", this->m_translateMatrix);
	Shader::Instance()->SendUniformData("scaleMatrix", this->m_scaleMatrix);
	Shader::Instance()->SendUniformData("rotateMatrix", this->m_rotateMatrix);
	
	Shader::Instance()->SendUniformData("material.shininess", this->m_shininess);
	Shader::Instance()->SendUniformData("material.ambient", this->m_ambient.r, this->m_ambient.g, this->m_ambient.b);
	Shader::Instance()->SendUniformData("material.diffuse", this->m_diffuse.r, this->m_diffuse.g, this->m_diffuse.b);
	Shader::Instance()->SendUniformData("material.specular", this->m_specular.r, this->m_specular.g, this->m_specular.b);


	this->m_texture.Bind();
	this->m_buffer.Render(Buffer::TRIANGLES);
	this->m_texture.Unbind();
}

void Quad::Update()
{
	//if (Input::Instance()->IsKeyPressed())
	//{
	//	if (Input::Instance()->GetKeyDown() == 'j')
	//	{
	//		this->m_position.x -= 0.001f;
	//	}
	//	if (Input::Instance()->GetKeyDown() == 'l')
	//	{
	//		this->m_position.x += 0.001f;
	//	}
	//	if (Input::Instance()->GetKeyDown() == 'i')
	//	{
	//		this->m_position.z -= 0.001f;
	//	}
	//	if (Input::Instance()->GetKeyDown() == 'k')
	//	{
	//		this->m_position.z += 0.001f;
	//	}
	//	if (Input::Instance()->GetKeyDown() == 'u')
	//	{
	//		this->m_position.y -= 0.001f;
	//	}
	//	if (Input::Instance()->GetKeyDown() == 'o')
	//	{
	//		this->m_position.y += 0.001f;
	//	}
	//	std::cout << "x: " << this->m_position.x << " y: " << this->m_position.y << " z: " << this->m_position.z << std::endl;
	//	//this->m_modelMatrix = glm::mat4(1.0f);
	//	//this->m_modelMatrix = glm::translate(this->m_modelMatrix, m_position);
	//	this->Translate(m_position);
	//}
}



void Quad::Translate(const glm::vec3& pos)
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

void Quad::Scale(const glm::vec3& s)
{
	this->m_scaleMatrix = glm::scale(this->m_scaleMatrix, s);
}

void Quad::Rotate(const glm::vec3& axis, const float& degree)
{
	this->m_rotateMatrix = glm::rotate(this->m_rotateMatrix, glm::radians(degree), axis);
}




