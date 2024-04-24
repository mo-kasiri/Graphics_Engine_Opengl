#pragma once
#include "glad.h"
#include <string>
class Buffer
{

public:
	enum VBOType {VERTEX_BUFFER, COLOR_BUFFER};

	enum ComponentType{ UV = 2, XY = 2, XYZ = 3, RGB = 3, RGBA = 4};

	enum FillType {SINGLE = GL_STATIC_DRAW, MULTIPLE = GL_DYNAMIC_DRAW};

	enum DataType {INT = GL_INT, FLOAT = GL_FLOAT, UNSIGNED_INT = GL_UNSIGNED_INT};

	enum DrawType {POINTS = GL_POINTS, TRIANGLES = GL_TRIANGLES, LINES = GL_LINES};

public:
	Buffer();

public:
	void CreateBuffer(GLuint totalVertices);

	void FillVBO(VBOType vboType,
				GLfloat* data,
				GLsizeiptr bufferSize,
				FillType fillType);

	void LinkBuffer(const std::string& attribute, VBOType vboType, ComponentType componentType, DataType dataType);

	void Render(DrawType drawType);

	void DestroyBuffer();

private:

	GLuint m_totalVertices;

	GLuint m_vertexVBO;
	GLuint m_colorVBO;

	GLuint m_VAO;

};

