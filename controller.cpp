#include "controller.h"


Controller::Controller()
{
	main_game = Game();
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
			main_game.getInput(QUIT); // ESC
		if (e.type == SDL_KEYDOWN)
		{
			//std::cout << e.key.keysym.sym << std::endl;
			switch(e.key.keysym.sym)
			{
			case 119:
				main_game.getInput(UP); // W
				break;
			case 115:
				main_game.getInput(DOWN); // S
				break;
			case 97:
				main_game.getInput(LEFT); // A
				break;
			case 100:
				main_game.getInput(RIGHT); // D
				break;
			case 32:
				main_game.getInput(WAIT); // SPACE
				break;
			case 27:
				main_game.getInput(QUIT); // ESC
				break;
			}
		}
	 }
}

void Controller::renderToView()
{
	int view_range = 5;
	int view_size = 11;
	main_view->clear();

	int x_offset = main_game.player->x - view_range;
	int y_offset = main_game.player->y - view_range;

	//int x_offset = main_game->player.x - view_range;
	//int y_offset = main_game->player.y - view_range;

	for(int i=0; i<view_size; i++){ // DRAW MAP TILES
		for(int j=0; j<view_size; j++){
				 
			if(j+x_offset < 0 || j+x_offset >= WIDTH || i+y_offset < 0 || i+y_offset >= HEIGHT)
			{
			}
			else
				main_view->drawSprite(j,i,main_game.map[j+x_offset][i+y_offset].graphic);
		}
	}

	for(int i=0; i<main_game.enemies.size();i++) // DRAW ENEMIES
	{
		main_view->drawSprite(main_game.enemies[i].x - x_offset ,main_game.enemies[i].y - y_offset, main_game.enemies[i].graphic);
	}

	main_view->drawSprite(5 ,5, main_game.player->graphic); // DRAW PLAYER
	//main_view->drawSprite(5 ,5, main_game->player.graphic); // DRAW PLAYER

	main_view->render();
	SDL_Delay(15);
}

void Controller::mainLoop()
{
	SDL_Event event;
	while(main_game.running)
	{
		handleInput(event);
		renderToView();
	}
	

}
