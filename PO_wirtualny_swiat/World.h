#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
class Organism;

using std::string;
using std::vector;
using std::array;
using std::stringstream;
class World
{
private:
	Organism*** board;
	int BoardSizeX;
	int BoardSizeY;
	vector<Organism*> organisms;
	stringstream infoStream ;
	bool isHumanAlive = false;
public:
	World(int sizeX, int sizeY);
	void drawWorld();
	void drawInfo();
	void performTurn();
	int getBoardSizeX();
	int getBoardSizeY();
	void humanDied();
	stringstream& getInfoStream();
	void sortOrganisms();
	void addOrganism(Organism* organism);
	void removeOrganism(Organism& removedOrganism);
	static void gotoxy(int x, int y);
	Organism*** getBoard();
	~World();
};