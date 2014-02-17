#ifndef CTRL_H
#define CTRL_H

#include "stdafx.h"
#include "game.h"
#include "view.h"

class Controller
{
public:
	Controller();
	~Controller();
	void handleInput(SDL_Event &e);
	void renderToView();
	void mainLoop();
	
private:
	Game *main_game;
	View *main_view;
};

#endif
