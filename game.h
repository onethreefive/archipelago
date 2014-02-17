#pragma once
#include "stdafx.h"
#include <random>

const int WIDTH = 11;
const int HEIGHT = 11;
enum TILE_GRAPHIC {G_GRASS, G_STONE_WALL, G_WATER, G_BAT, G_KNIGHT, G_PLAYER, G_CORPSE};

enum enemy_type {BAT, KNIGHT};

enum tile_type {FLOOR, WALL};

enum input_type {UP, DOWN, LEFT, RIGHT, WAIT, RESET, QUIT};

class Tile
{
public:
	Tile();
	Tile(bool walk, TILE_GRAPHIC type);
	//~Tile();

	bool walkable;
	TILE_GRAPHIC graphic;

private:
	
};


class Creature
{
public:

	Creature();
	Creature(int x_start, int y_start, enemy_type type);
	~Creature();

	bool move(int dx, int dy, Tile (&curr_map)[WIDTH][HEIGHT]);

	void recieveDamage(int damage);

	void attack(Creature &victim);

	void turnAI();

	bool dead;
	bool aggro;

	std::string name;
	int x;
	int y;
	TILE_GRAPHIC graphic;

	int health_max;
	int spirit_max;
	int strength;
	int armour;

	int health;
	int spirit;
};


struct PC
{
	TILE_GRAPHIC graphic;
	int x;
	int y;
};

class Game
{
public:
	Game();
	//~Game();
	Tile map[WIDTH][HEIGHT];

	std::vector<Creature> enemies;
	Creature *player;

	void generateMap();

	void getInput(input_type input);

	void execute_turn();

	void turnAI(Creature &creature);

	bool moveOrAttack(Creature &creature, int dx, int dy);

	bool running;
	
private:
	
};