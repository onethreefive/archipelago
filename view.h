#include "stdafx.h"

class View
{
public:
	
	View(std::string name);

	~View();
	
	int init();

	void clear();
	void render();

	void drawRect(int x, int y, int type);

	SDL_Texture* loadTexture(const char* image, SDL_Renderer* ren);

private:

	int sWidth;
	int sHeight;
	SDL_Window *window;
	SDL_Renderer *renderer;
};