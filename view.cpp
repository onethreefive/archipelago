#include "view.h"



View::View(std::string name)
{
	sWidth = TILE_SIZE*11;
	sHeight = TILE_SIZE*11;
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

	textures.push_back(loadTexture("floor.bmp", renderer));
	textures.push_back(loadTexture("brick wall.bmp", renderer));
	textures.push_back(loadTexture("player.bmp", renderer));
	textures.push_back(loadTexture("bat.bmp", renderer));

	return 1;
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

void View::drawSprite(int x, int y, int graphic)
{
	SDL_Rect rect = {x*TILE_SIZE,y*TILE_SIZE,TILE_SIZE,TILE_SIZE};

	switch(graphic)
	{
	//case G_GRASS:
	case 0:
		SDL_RenderCopy(renderer, textures[0], NULL, &rect);
		break;
	//case G_STONE_WALL:
	case 1:
		SDL_RenderCopy(renderer, textures[1], NULL, &rect);
		break;
	//case G_WATER:
	case 2:
		SDL_RenderCopy(renderer, textures[0], NULL, &rect);
		break;
	//case G_BAT:
	case 3:
		SDL_RenderCopy(renderer, textures[3], NULL, &rect);
		break;
	//case G_KNIGHT:
	case 4:
		SDL_RenderCopy(renderer, textures[2], NULL, &rect);
		break;
	//case G_PLAYER:
	case 5:
		SDL_RenderCopy(renderer, textures[2], NULL, &rect);
		break;
	//case G_CORPSE:
	case 6:
		SDL_RenderCopy(renderer, textures[0], NULL, &rect);
		break;
	}
}
