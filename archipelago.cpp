// archipelago.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "view.h"
//#include "game.h"
#include "controller.h"

int _tmain(int argc, _TCHAR* argv[])
{

	/*View mainView("fsd");

	Game game;
	
	SDL_Event e;
	bool quit = false;
	while(!quit)
	{
		 while (SDL_PollEvent(&e)){
            //If user closes he window
            if (e.type == SDL_QUIT)
                quit = true;
			if (e.type == SDL_KEYDOWN)
			{
				//std::cout << e.key.keysym.sym << std::endl;
				switch(e.key.keysym.sym)
				{
				case 119:
					game.getInput(UP); // W
					break;
				case 115:
					game.getInput(DOWN); // S
					break;
				case 97:
					game.getInput(LEFT); // A
					break;
				case 100:
					game.getInput(RIGHT); // D
					break;
				case 32:
					game.getInput(WAIT); // SPACE
					break;
				case 27:
					quit = true;
					break;
				}
			}
		 }

		 mainView.clear();

		 for(int i=0; i<HEIGHT; i++){ // DRAW MAP TILES
			 for(int j=0; j<WIDTH; j++){
				 
				 mainView.drawRect(j,i,game.map[j][i].graphic);
			 }
		 }

		 for(int i=0; i<game.enemies.size();i++) // DRAW ENEMIES
		 {
			 mainView.drawRect(game.enemies[i].x ,game.enemies[i].y, game.enemies[i].graphic);
		 }

		 mainView.drawRect(game.player->x ,game.player->y, game.player->graphic); // DRAW PLAYER

		 mainView.render();
		 SDL_Delay(15);
	}
	mainView.~View();*/

	Controller main_controller;

	main_controller.mainLoop();

	return 0;
}


