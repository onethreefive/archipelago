#include "view.h"



View::View(std::string name)
{
	sWidth = 640;
	sHeight = 480;
	this->window = nullptr;
	this->renderer = nullptr;

	init();
	std::cout << "created view" << std::endl;
}

View::~View()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void View::clear()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0,0);
	SDL_RenderClear(this->renderer);
}
void View::render()
{
	SDL_RenderPresent(this->renderer);
}

int View::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

	this->window = SDL_CreateWindow("Hello World!", 100, 100, sWidth, sHeight, 0);
	if (this->window == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
	return 1;
}

void View::drawRect(int x, int y, int graphic)
{
	SDL_Rect rect = {x*40,y*40,40,40};
	switch(graphic)
	{
	//case G_GRASS:
	case 0:
		SDL_SetRenderDrawColor(this->renderer, 40, 180, 120, 0);
		break;
	//case G_STONE_WALL:
	case 1:
		SDL_SetRenderDrawColor(this->renderer, 50, 50, 50, 0);
		break;
	//case G_WATER:
	case 2:
		SDL_SetRenderDrawColor(this->renderer, 10, 10, 255,0);
		break;
	//case G_BAT:
	case 3:
		SDL_SetRenderDrawColor(this->renderer, 160, 10, 160,0);
		break;
	//case G_KNIGHT:
	case 4:
		SDL_SetRenderDrawColor(this->renderer, 180, 180, 180,0);
		break;
	//case G_PLAYER:
	case 5:
		SDL_SetRenderDrawColor(this->renderer, 200, 10, 20,0);
		break;
	//case G_CORPSE:
	case 6:
		SDL_SetRenderDrawColor(this->renderer, 200, 180, 20, 150);
		break;
	}

	SDL_RenderFillRect(this->renderer, &rect);
	SDL_SetRenderDrawColor(this->renderer, 100, 100, 20,0);
	SDL_RenderDrawRect(this->renderer, &rect);
}

SDL_Texture* View::loadTexture(const char* image, SDL_Renderer* ren)
{
	SDL_Surface* surface = nullptr;
	surface = SDL_LoadBMP(image);
	if(surface == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if(texture == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	
	return texture;
}