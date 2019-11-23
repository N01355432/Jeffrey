#pragma once

#include <SDL.h>
#include <string>

class Character
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;

	//Movement Speed in pixel per second
	float MSpeed;

	//Frame Counter
	float FCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];

public:
	Character(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Character();

	void Update(float delta, const Uint8* keyState);
	void Draw(SDL_Renderer* renderTarget);

	SDL_Rect positionRect;
};

