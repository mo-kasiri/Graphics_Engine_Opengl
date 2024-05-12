#include <iostream>
#include "Screen.h"
#include "glad.h"

Screen::Screen()
{
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;
	//std::cout << "inside screen instructor" << std::endl;
}

Screen::~Screen() {
	//std::cout << "insid screen destructor" << std::endl;
}

Screen* Screen::Instance()
{	// declare it as static so it will be created only once, for the lifetime of the program.
	// If you remove static it will be created whenever the Instance method is called
	// Static variables in a Function: When a variable is declared as static, space for it gets allocated for the lifetime of the program
	static Screen* screen = new Screen; 
	return screen;
}


bool Screen::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "Error initializing SDL" << std::endl;
		return false;
	};

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);



	this->window = SDL_CreateWindow("Graphics Engine",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								1280, 720,
								SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cout << "Error creating SDL window." << std::endl;
		return false;
	}

	this->context = SDL_GL_CreateContext(window);

	if (context == nullptr) {
		std::cout << "Error creating SDL context." << std::endl;
		return false;
	}

	if (!gladLoadGL())
	{
		std::cout << "Error Loading Glad Extentions." << std::endl;
		return false;
	}

	return true;
}

void Screen::ClearScreen(const float& r, const float& g, const float& b, const float& a)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r,g,b,a);
}

void Screen::Present()
{
	SDL_GL_SwapWindow(this->window);
}

void Screen::ShutDown()
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

