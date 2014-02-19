#include "stdafx.h"

const int TILE_SIZE = 48;

class View
{
public:
	
	View(std::string name);

	~View();
	
	int init();

	void clear();
	void render();

	void drawSprite(int x, int y, int graphic);

	SDL_Texture* loadTexture(const char* image, SDL_Renderer* ren);


private:

	int tile_size;
	int sWidth;
	int sHeight;

	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<SDL_Texture*> textures;
};