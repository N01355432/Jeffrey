#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include "Char.h"

int main(int argc, char* argv[])
{
	const int FPS = 60;
	int frameTime = 0;

	// Initializing and loading variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	SDL_Rect playerRect;
	SDL_Rect playerPos;

	//Player Position and Size
	playerPos.x = playerPos.y = 0;
	playerPos.w = playerPos.h = 32;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	//Time Variables
	int prevTime = 0.0f;
	int currentTime = 0.0f;
	float deltaTime = 0.0f;

	const Uint8* keyState;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
	else
	{
		//Allows to use PNG and JPG Images
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags))
			std::cout << "Image Initialization Error: " << IMG_GetError() << std::endl;
			
		window = SDL_CreateWindow("SDL Warper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//Loading the Character Sprite
		//Use PNG Files to have Transparent Backgrounds
		Character player(renderTarget, "Character.png", 0, 0, 3, 4);

		bool isRunning = true;
		SDL_Event ev;

		while (isRunning)
		{
			//Adjustment to different refresh rates
			prevTime = currentTime;
			currentTime = SDL_GetTicks();
			deltaTime = (currentTime - prevTime) / 1000.0f;

			//Events input such as keyboard presses
			while (SDL_PollEvent(&ev) != 0)
			{
				if (ev.type == SDL_QUIT)
					isRunning = false;

				//Creates Unwanted Stutters
				/*else if (ev.type == SDL_KEYDOWN)
				{
					switch (ev.key.keysym.sym)
					{
					//Right Key Move Right
					case SDLK_RIGHT:
						playerPos.x += MSpeed + deltaTime;
					}
				}*/
			}

			keyState = SDL_GetKeyboardState(NULL);

			player.Update(deltaTime, keyState);

			SDL_RenderClear(renderTarget);
			player.Draw(renderTarget);
			SDL_RenderPresent(renderTarget);
		}

		/*if (window == NULL)
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
		else
		{
			// Window Creation
			windowSurface = SDL_GetWindowSurface(window);
			imageSurface = SDL_LoadBMP("test.bmp");

			if (imageSurface == NULL)
				std::cout << "Image loading Error: " << SDL_GetError() << std::endl;
			else
			{
				//Drawing the current image to the window
				SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
				SDL_UpdateWindowSurface(window);
				SDL_Delay(2000);
			}
		}*/
	}

	//Clearing Memory
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	window = nullptr;
	renderTarget = nullptr;

	SDL_Quit;
	IMG_Quit;

	return 0;
}

