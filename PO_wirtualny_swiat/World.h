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
	int boardSizeX;
	int boardSizeY;
	vector<Organism*> organisms;
	stringstream infoStream ;
	bool humanAlive = false;
	bool gameSaved = false;

	void sortOrganisms();
public:
	World(int sizeX, int sizeY);
	
	void drawWorld();
	void drawInfo();
	void performTurn();
	
	void makeSave();
	void loadSave();

	void humanDied();
	void addOrganism(Organism* organism);
	void removeOrganism(Organism& removedOrganism);

	void setOrganism(Organism* organism, int x, int y);
	Organism* getOrganism(int x, int y);

	int getBoardSizeX();
	int getBoardSizeY();
	stringstream& getInfoStream();
	
	static void gotoxy(int x, int y);
	

	~World();
};