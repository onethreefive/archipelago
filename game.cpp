#include "game.h"

Tile::Tile()
{
	walkable = true;
	graphic = G_GRASS;
}

Tile::Tile(bool walk, TILE_GRAPHIC graph)
{
	walkable = walk;
	graphic = graph;
}

Creature::Creature(int x_start, int y_start, enemy_type type)
{
	x = x_start;
	y = y_start;

	name = " ";
	dead = false;
	aggro = true;

	switch(type)
	{
	case BAT:

		name = "cave bat";
		graphic = G_BAT;

		health_max = 4;
		spirit_max = 4;
		strength = 3;
		armour = 1;

		health = health_max;
		spirit = spirit_max;

		break;
	case KNIGHT:

		name = "death knight";
		graphic = G_KNIGHT;

		health_max = 8;
		spirit_max = 8;
		strength = 5;
		armour = 2;

		health = health_max;
		spirit = spirit_max;
		break;
	}
}

Creature::~Creature()
{
}

void Creature::recieveDamage(int damage)
{
	int damage_taken = 0;
	if (damage > armour)
	{
		damage_taken = damage - armour;
		this->health = health - damage_taken;
	}
	std::cout << name.c_str() << " takes " << damage_taken << " damage" << std::endl;
	if (health <=0)
	{
		dead = true;
		graphic = G_CORPSE;
		std::cout << name.c_str() << " dies" << std::endl;
	}
}

bool Creature::move(int dx, int dy, Tile (&curr_map)[WIDTH][HEIGHT])
{
	int check_x;
	int check_y;

	check_x = x + dx;
	check_y = y + dy;

	if(curr_map[check_x][check_y].walkable)
	{
		this->x = check_x;
		this->y = check_y;
		std::cout << "succesfully moved player" << std::endl;
		return true;
	}

	else
		return false;
}

Game::Game()
{
	generateMap();

	int startX = 5;
	int startY = 5;

	while(!map[startX][startY].walkable)
	{	
		srand(time(nullptr)); // get new seed
		startX = rand() % WIDTH;
		startY = rand() % WIDTH;
	}

	player = new Creature(startX, startY, KNIGHT);
	player->graphic = G_PLAYER;
	player->name = "player";
	
	enemies.push_back(Creature(2,7, BAT));

	running = true;
}

void Game::generateMap()
{
	for(int y=0; y<HEIGHT; y++){
		for(int x=0; x<WIDTH; x++){
			if(x == 0 || x == WIDTH-1 || y == 0 || y == HEIGHT-1)
				map[x][y] = Tile(false, G_STONE_WALL);
			else
				map[x][y] = Tile(true, G_GRASS);
		}
	}
}

void Game::execute_turn()
{
	for(int i=0; i<enemies.size(); i++)
	{
		turnAI(enemies[i]);
	}
}


void Game::turnAI(Creature &creature)
{
	if(!creature.dead)
	{
		srand(time(nullptr));

		int dir = rand()%4;

		switch(dir)
		{
		case 0:
			moveOrAttack(creature, 0, -1);
			break;
		case 1:
			moveOrAttack(creature, 0, 1);
			break;
		case 2:
			moveOrAttack(creature, -1, 0);
			break;
		case 3:
			moveOrAttack(creature, 1, 0);
			break;
		}
	}
}

bool Game::moveOrAttack(Creature &creature, int dx, int dy)
{
	int check_x;
	int check_y;

	check_x = creature.x + dx;
	check_y = creature.y + dy;

	for(int i=0; i<enemies.size(); i++)
	{
		if(!enemies[i].dead && check_x == enemies[i].x && check_y == enemies[i].y)
		{
			std::cout << creature.name.c_str() << " attacks " << enemies[i].name.c_str() << std::endl;
			enemies[i].recieveDamage(creature.strength);
			return true;
		}
	}
	if(!player->dead && check_x == player->x && check_y == player->y)
	{
		std::cout << creature.name.c_str() << " attacks " << player->name.c_str() << std::endl;
			player->recieveDamage(creature.strength);
			return true;
	}

	if(map[check_x][check_y].walkable)
	{
		creature.x = check_x;
		creature.y = check_y;
		//std::cout << "succesfully moved player" << std::endl;
		return true;
	}
	else
		//std::cout << "blocked" << std::endl;
		return false;
}

void Game::getInput(input_type input)
{
	bool completed_turn = false;
	switch(input)
	{
	case UP:
		completed_turn = moveOrAttack(*player, 0, -1);
		break;
	case DOWN:
		completed_turn = moveOrAttack(*player, 0, 1);
		break;
	case LEFT:
		completed_turn = moveOrAttack(*player, -1, 0);
		break;
	case RIGHT:
		completed_turn = moveOrAttack(*player, 1, 0);
		break;
	case WAIT:
		completed_turn = true;
		break;
	case QUIT:
		running = false;
		break;
	}

	if(completed_turn)
		execute_turn();
}
