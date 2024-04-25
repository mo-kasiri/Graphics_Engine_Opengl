#include "Buffer.h"
#include "Shader.h"

Buffer::Buffer()
{
	m_totalVertices = 0;
	m_vertexVBO = 0;
	m_colorVBO = 0;
	this->m_textureVBO = 0;
	m_VAO = 0;
}

void Buffer::CreateBuffer(GLuint totalVertices)
{
	glGenBuffers(1, &this->m_vertexVBO);
	glGenBuffers(1, &this->m_colorVBO);
	glGenBuffers(1, &this->m_textureVBO);
	glGenVertexArrays(1, &this->m_VAO);

	this->m_totalVertices = totalVertices;
}

void Buffer::FillVBO(VBOType vboType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType)
{
	glBindVertexArray(this->m_VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, vboType == VBOType::VERTEX_BUFFER ? this->m_vertexVBO : this->m_colorVBO);

		if (vboType == VBOType::VERTEX_BUFFER)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexVBO);
		}
		else if (vboType == VBOType::COLOR_BUFFER)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->m_colorVBO);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->m_textureVBO);
		}
		glBufferData(GL_ARRAY_BUFFER, bufferSize, data, fillType); // Copies data into the gpu memory
	glBindVertexArray(0);
}


void Buffer::LinkBuffer(const std::string& attribute, VBOType vboType, ComponentType componentType, DataType dataType)
{
	GLuint shaderProgramID = Shader::Instance()->GetShaderProgramID();

	GLint attribLocationID = glGetAttribLocation(shaderProgramID, attribute.c_str());

	glBindVertexArray(this->m_VAO);

		//glBindBuffer(GL_ARRAY_BUFFER, vboType == VBOType::VERTEX_BUFFER ? this->m_vertexVBO : this->m_colorVBO);
		if (vboType == VBOType::VERTEX_BUFFER)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->m_vertexVBO);
		}
		else if (vboType == VBOType::COLOR_BUFFER)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->m_colorVBO);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->m_textureVBO);
		}
		glVertexAttribPointer(attribLocationID, componentType, dataType, GL_FALSE, componentType * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(attribLocationID);

	glBindVertexArray(0);

}

void Buffer::Render(DrawType drawType)
{
	glBindVertexArray(this->m_VAO);
	glDrawArrays(drawType, 0, this->m_totalVertices);
	glBindVertexArray(0);
}

void Buffer::DestroyBuffer()
{
	glDeleteBuffers(1, &this->m_vertexVBO);
	glDeleteBuffers(1, &this->m_colorVBO);
	glDeleteBuffers(1, &this->m_textureVBO);
	glDeleteVertexArrays(1, &this->m_VAO);
	
}
