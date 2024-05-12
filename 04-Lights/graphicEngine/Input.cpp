#include "Input.h"
#include <iostream>


Input* Input::Instance()
{
	static Input* inputObject = new Input();
	return inputObject;
}

Input::Input()
{
	this->m_keyUp = 0;
	this->m_keyDown = 0;

	this->m_isXClicked = false;
	this->m_isKeyPressed = false;

	this->m_isLeftButtonClicked = false;
	this->m_isRightBottonClicked = false;
	this->m_isMiddleButtonClicked = false;

	this->m_mouseMotionX = 0;
	this->m_mouseMotionY = 0;

	this->m_mousePositionX = 0;
	this->m_mousePositionY = 0;

}

bool Input::IsXCliked()
{
	return this->m_isXClicked;
}

bool Input::IsKeyPressed()
{
	return this->m_isKeyPressed;
}

char Input::GetKeyUp()
{
	return this->m_keyUp;
}

char Input::GetKeyDown()
{
	return this->m_keyDown;
}

bool Input::IsLeftButtonClicked()
{
	return this->m_isLeftButtonClicked;
}

bool Input::IsRightButtonClicked()
{
	return this->m_isRightBottonClicked;
}

bool Input::IsMiddleButtonClicked()
{
	return this->m_isMiddleButtonClicked;
}

int Input::GetMousePositionX()
{
	return this->m_mousePositionX;
}

int Input::GetMousePositionY()
{
	return this->m_mousePositionY;
}

int Input::GetMouseMotionX()
{
	return this->m_mouseMotionX;
}

int Input::GetMouseMotionY()
{
	return this->m_mouseMotionY;
}


void Input::Update()
{
	SDL_Event events;

	this->m_mouseMotionX = 0;
	this->m_mouseMotionY = 0;

	this->m_mousePositionX = 0;
	this->m_mousePositionY = 0;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

			// Keyboard
			case SDL_KEYDOWN:
			{
				this->m_isKeyPressed = true;
				this->m_keyDown = events.key.keysym.sym;
				break;
			}
			case SDL_KEYUP:
			{
				this->m_isKeyPressed = false;
				this->m_keyUp = events.key.keysym.sym;
				break;
			}
			
			// Mouse
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (events.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					this->m_isLeftButtonClicked = true;
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					this->m_isRightBottonClicked = true;
					break;
				}
				case SDL_BUTTON_MIDDLE:
				{
					this->m_isMiddleButtonClicked = true;
					break;
				}
				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						this->m_isLeftButtonClicked = false;
						break;
					}
					case SDL_BUTTON_RIGHT:
					{
						this->m_isRightBottonClicked = false;
						break;
					}
					case SDL_BUTTON_MIDDLE:
					{
						this->m_isMiddleButtonClicked = false;
						break;
					}
				}
				break;
			}

			// Window
			case SDL_QUIT:
			{
				this->m_isXClicked = true;
				break;
			}

			case SDL_MOUSEMOTION:
			{
				this->m_mouseMotionX = events.motion.xrel;
				this->m_mouseMotionY = events.motion.yrel;
				
				this->m_mousePositionX = events.motion.x;
				this->m_mousePositionY = events.motion.y;
				break;
			}

		}
	}
}