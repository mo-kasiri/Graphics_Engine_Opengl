#include <iostream>
#include <SDL.h>
#include "glad.h"

#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include "Quad.h"
#include "Camera.h"
#include <glm.hpp>


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

	Shader::Instance()->CompileShaders("Shaders/Main.vert.c", Shader::ShaderType::VERTEX_SHADER);
	Shader::Instance()->CompileShaders("Shaders/Main.frag.c", Shader::ShaderType::FRAGMENT_SHADER);

	Shader::Instance()->AttachShaders();
	if (!Shader::Instance()->LinkProgram()) {
		return 0;
	}

	
	Camera camera;
	Quad quad;
	//quad.Scale(glm::vec3(0.25, 0.5, 0.25));
	

	// ================================================================== main while
	while (isAppRunning)
	{
		Input::Instance()->Update();

		isAppRunning = !Input::Instance()->IsXCliked();

		/*char keyPressed = Input::Instance()->GetKeyDown();

		
		static int i = 0;
		if (Input::Instance()->IsLeftButtonClicked())
		{
			i++;
			std::cout << "Left Button " << i << std::endl;
		}
		else {
			i = 0;
		}


		int mouseX = Input::Instance()->GetMousePositionX();
		int mouseY = Input::Instance()->GetMousePositionY();

		std::cout << "Mouse at Position " << mouseX << ", " << mouseY << std::endl;*/
		

		Screen::Instance()->ClearScreen(0.2f, 0.3f, 0.3f, 1.0f);

		camera.Update();

		quad.Update();
		quad.Render();
		

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