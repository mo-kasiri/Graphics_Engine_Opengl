#pragma once
#include <glm.hpp>
#include <queue>
#include <gtc/matrix_transform.hpp>
#include <iostream>
//#include <vector>
#include "Shader.h"
#include "Buffer.h"

struct Vertices {
	unsigned int size;
	GLfloat* data;
	GLuint* indices;
};

class GridLines
{
	public:
		GridLines(const unsigned int& YaxisDivision, const unsigned int& XaxisDivision);
		~GridLines();

		Vertices CreateMesh(const unsigned int& YaxisDivision, const unsigned int& XaxisDivision);
		void Render();
		void Update();


		void Translate(const glm::vec3 & pos);
		void Scale(const glm::vec3 & s);
		void Rotate(const glm::vec3 & axis, const float& degree);

	private:
		Buffer m_buffer;

		//GLfloat* m_vertices;

		glm::mat4 m_translateMatrix;
		glm::mat4 m_scaleMatrix;
		glm::mat4 m_rotateMatrix;
		glm::vec3 m_position;
};

