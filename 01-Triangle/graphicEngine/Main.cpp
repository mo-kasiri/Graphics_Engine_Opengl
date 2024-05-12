#include <iostream>
#include <SDL.h>
#include "glad.h"

#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include <glm.hpp>
#include <SDL_image.h>

#include "Triangle.h"


bool isAppRunning = true;


int main(int argc, char* argv[])
{
	Screen::Instance()->Initialize();

	if (!Shader::Instance()->CreateProgram())
	{
		return 0;
	}

	if (!Shader::Instance()->CreateShaders()) 
	{
		return 0;
	}

	Shader::Instance()->CompileShaders("Shaders/vert.glsl", Shader::ShaderType::VERTEX_SHADER);
	Shader::Instance()->CompileShaders("Shaders/frag.glsl", Shader::ShaderType::FRAGMENT_SHADER);

	Shader::Instance()->AttachShaders();
	if (!Shader::Instance()->LinkProgram()) {
		return 0;
	}

	Triangle triangle;
	//triangle.Scale(glm::vec3(2.0, 2.0, 2.0));
	
	
	// ================================================================== main while
	while (isAppRunning)
	{
		Input::Instance()->Update();

		isAppRunning = !Input::Instance()->IsXCliked();

		Screen::Instance()->ClearScreen(0.2f, 0.3f, 0.3f, 1.0f);

		triangle.Render();
		triangle.Update();


		// update / render 
		Screen::Instance()->Present();
	}
	// =================================================================== End of main while


	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();

	Screen::Instance()->ShutDown();
	
	return 0;
}