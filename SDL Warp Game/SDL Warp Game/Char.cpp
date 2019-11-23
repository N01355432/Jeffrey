#include "Char.h"
#include <SDL_image.h>
#include <iostream>

Character::Character(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (surface == NULL)
		std::cout << "Texture Surface Error: " << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);

		//A Quick Check
		if (texture == NULL)
			std::cout << "Texture Error: " << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	isActive = false;

	static int charNumber = 0;
	charNumber++;

	//Scancode Compensating for Different Keyboards and Eliminates Stutter
	if (charNumber = 0);
	{
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}
	//Character Movement Speed pixel per Second
	MSpeed = 200.0f;
}

Character::~Character()
{
	SDL_DestroyTexture(texture);
}

void Character::Update(float delta, const Uint8* keyState)
{
	isActive = true;

	if (keyState[keys[0]])
	{
		//Jumping Motion in Sprite Sheet
		positionRect.y -= MSpeed * delta;
		cropRect.y = frameHeight * 3;
	}
	else if (keyState[keys[1]])
	{
		//Down Key Motion
		positionRect.y += MSpeed * delta;
		cropRect.y = 0;
	}
	else if (keyState[keys[2]])
	{
		//Left Movement
		positionRect.x -= MSpeed * delta;
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[3]])
	{
		//Right Movement
		positionRect.x += MSpeed * delta;
		cropRect.y = frameHeight * 2;
	}
	else
		isActive = false;

	if (isActive)
	{
		FCounter += delta;

//Animation Speed According to Refresh Rate
//Example is 0.25f will refresh 4 times per 1 second

		if (FCounter >= 0.25f)
		{
			FCounter = 0;
			cropRect.x += frameWidth;
			
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;
		}
	}
	else
	{
		//Standing Still Pose in the Top Middle of Sprite Sheet
		FCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Character::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}