#include <queue>
#include "GridLines.h"

GridLines::GridLines(const unsigned int& YaxisDivision, const unsigned int& XaxisDivision)
{
	//float vertices[] = {
	//	 0.5f,  0.5f, 0.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//};

	this->m_position = glm::vec3(0.0f);

	this->m_translateMatrix = glm::mat4(1.0f);
	this->m_scaleMatrix = glm::mat4(1.0f);
	this->m_rotateMatrix = glm::mat4(1.0f);

	Vertices vertices = this->CreateMesh(YaxisDivision, XaxisDivision);

	std::cout << vertices.size * 4 << std::endl;
	
	this->m_buffer.CreateBuffer(vertices.size/3);
	this->m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices.data, vertices.size * sizeof(float), Buffer::SINGLE);
	vertices.data = nullptr;
	//this->m_buffer.FillEBO(vertices.indices, 6 * sizeof(float), Buffer::SINGLE);
	//vertices.indices = nullptr;
	this->m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
}

GridLines::~GridLines()
{
	this->m_buffer.DestroyBuffer();
}

Vertices GridLines::CreateMesh(const unsigned int& YaxisDivision, const unsigned int& XaxisDivision)
{
	float ratioX = 2.0f / float(YaxisDivision);
	float ratioY = 2.0f / float(XaxisDivision);

	GLfloat y = 1.0f;
	unsigned int j = 0;
	const unsigned int totalNumberOfVertices = (YaxisDivision + 1) * (XaxisDivision + 1);
	const unsigned int totalNumberOfIndices =  (YaxisDivision * 2) + (XaxisDivision * 2);
	unsigned int k = 0;

	GLfloat* vertices = new GLfloat[totalNumberOfVertices]; // Allocate memory dynamically
	GLuint* HorizontalIndices = new GLuint[totalNumberOfIndices];

	for (unsigned int i = 0; i < totalNumberOfVertices; i++)
	{
		if (j * ratioX > 2.0f)
		{
			y -= ratioY;
			j = 0;
		}
		
		vertices[k] = -1.0f + j * ratioX;
		vertices[++k] = y;
		vertices[++k] = 0.0;
		k++;
		j++;
	};

	
	for (unsigned int l = 0; l < XaxisDivision; l++)
	{
		if (l % 2 == 0)
		{
			HorizontalIndices[l] = l * XaxisDivision;
		}
		else if (l % 2 == 1)
		{
			HorizontalIndices[l] = l * XaxisDivision - 1;
		}
	}

	return { k, vertices, HorizontalIndices };
}


void GridLines::Render()
{
	Shader::Instance()->SendUniformData("translateMatrix", this->m_translateMatrix);
	Shader::Instance()->SendUniformData("scaleMatrix", this->m_scaleMatrix);
	Shader::Instance()->SendUniformData("rotateMatrix", this->m_rotateMatrix);

	this->m_buffer.Render(Buffer::POINTS);
}

void GridLines::Update()
{
}

void GridLines::Translate(const glm::vec3& pos)
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

void GridLines::Scale(const glm::vec3& s)
{
	this->m_scaleMatrix = glm::scale(this->m_scaleMatrix, s);
}

void GridLines::Rotate(const glm::vec3& axis, const float& degree)
{
	this->m_rotateMatrix = glm::rotate(this->m_rotateMatrix, glm::radians(degree), axis);
}


