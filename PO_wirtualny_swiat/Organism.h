#pragma once

#include <iostream>
#include <string>

using std::string;

class World;


class Organism
{
protected:
	int strength;
	int initiative;
	int posX;
	int posY;
	unsigned int age = 1;
	char prefix;
	string name;
	World& currWorld; 
public:
	Organism(int strength, int initiative, int posX, int posY, char prefix, string name, World& currWorld);
	virtual void action() = 0;
	virtual bool collision(Organism* invader) = 0;
	virtual void makeMove(int& newX, int& newY);
	virtual bool hasBlocked(Organism* invader);
	void draw();
	int getPosX();
	int getPosY();
	int getAge();
	int getStrength();
	int getInitiative();
	char getPrefix();
	string getName();
	void setStrength(int newStrength);
	void setNewPosition(int newX, int newY);
	void setAge(int newAge);
	void incrementAge();
	void decrementAge();
	friend std::ostream& operator<<(std::ostream& os, const Organism& Organism);
	virtual ~Organism();
};