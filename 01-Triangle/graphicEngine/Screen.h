#pragma once
#include <SDL.h>
class Screen
{
public:
	static Screen* Instance();

public:
	bool Initialize();
	void ClearScreen(const float& r = 0.f, const float& g = 0.f, const float& b = 0.f, const float& a = 0.f);
	void Present(); // SwapBuffer
	void ShutDown();



private:
	SDL_Window* window;
	SDL_GLContext context;

private:
	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);
	~Screen();
};

