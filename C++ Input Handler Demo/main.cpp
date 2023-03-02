#pragma once

#include "Input.h"

// demo usage only.
#include <iostream>
using namespace std;

SDL_Window* m_window;
SDL_Renderer* m_renderer;

/*
-------------- IMPORTANT NOTE --------------

	Don't forget to be clicked into
	the window before testing inputs.
		  I kept forgetting...

--------------------------------------------
*/

int main(int argc, char* argv[])
{
	// SDL initialization.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		// Error
		cout << "Failed to intialise SDL. Error: " << SDL_GetError() << endl;
	}

	// Window and renderer creation.
	m_window = SDL_CreateWindow("Input Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, SDL_WINDOW_RESIZABLE);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	// INPUT HANDLER USAGE -- START

	// Input initalization.
	Input::Initialize();

	while (true)
	{

		// Input Update has to be called first to store the previous frame's keyboard data.
		Input::Update();

		/*EventHandler() needs to come after Update and 
		before key checks as SDL has to gather pending input data
		and this function calls "SDL_PollEvent()" which subsquentally 
		calls "SDL_PumpEvent()" which does that. Not sure if SDL_PumpEvent is 
		safe to directly call though... either way, this way it provides event polling too.*/
		if (!Input::EventHandler()) 
		{
			break;
		}

		// Key checks

		if (Input::GetKeyDown(SDL_SCANCODE_W)) cout << "W was pressed" << endl;
		if (Input::GetKeyUp(SDL_SCANCODE_S)) cout << "S was released" << endl;

		if (Input::GetKey(SDL_SCANCODE_A)) cout << "A is held" << endl;
		if (Input::GetKey(SDL_SCANCODE_D)) cout << "D is held" << endl;


	}

	// Input cleanup.
	Input::Cleanup();

	// INPUT HANDLER USAGE -- END

	// Window cleanup.
	SDL_DestroyWindow(m_window);

	m_window = nullptr;

	// Renderer cleanup.
	SDL_DestroyRenderer(m_renderer);

	m_renderer = nullptr;

	// SDL cleanup.
	SDL_Quit();

	return 0;
}