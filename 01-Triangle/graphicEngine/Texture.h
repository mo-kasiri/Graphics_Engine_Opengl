#pragma once
#include <iostream>
#include <SDL_image.h>
#include "glad.h"
class Texture
{

public:

	Texture();

	void Bind();
	bool Load(const std::string& filename);
	void Unbind();
	void Unload();

private:
	GLuint m_ID;
};

