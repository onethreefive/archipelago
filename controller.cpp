#include "controller.h"


Controller::Controller()
{
	main_game = new Game();
	main_view = new View("archipelago");
}

Controller::~Controller()
{
	main_view->~View();
}

void Controller::handleInput(SDL_Event &e)
{
	 while (SDL_PollEvent(&e))
	 {
		//If user closes he window
		if (e.type == SDL_QUIT)
			main_game->getInput(QUIT); // ESC
		if (e.type == SDL_KEYDOWN)
		{
			//std::cout << e.key.keysym.sym << std::endl;
			switch(e.key.keysym.sym)
			{
			case 119:
				main_game->getInput(UP); // W
				break;
			case 115:
				main_game->getInput(DOWN); // S
				break;
			case 97:
				main_game->getInput(LEFT); // A
				break;
			case 100:
				main_game->getInput(RIGHT); // D
				break;
			case 32:
				main_game->getInput(WAIT); // SPACE
				break;
			case 27:
				main_game->getInput(QUIT); // ESC
				break;
			}
		}
	 }
}

void Controller::renderToView()
{
	main_view->clear();

	for(int i=0; i<HEIGHT; i++){ // DRAW MAP TILES
		for(int j=0; j<WIDTH; j++){
				 
			main_view->drawRect(j,i,main_game->map[j][i].graphic);
		}
	}

	for(int i=0; i<main_game->enemies.size();i++) // DRAW ENEMIES
	{
		main_view->drawRect(main_game->enemies[i].x ,main_game->enemies[i].y, main_game->enemies[i].graphic);
	}

	main_view->drawRect(main_game->player->x ,main_game->player->y, main_game->player->graphic); // DRAW PLAYER

	main_view->render();
	SDL_Delay(15);
}

void Controller::mainLoop()
{
	SDL_Event event;
	while(main_game->running)
	{
		handleInput(event);
		renderToView();
	}
	

}
