#pragma once
#include "Animal.h"
class World;
class Animal;

class Turtle : public Animal
{
public:
	Turtle(int posX, int posY, World& currWorld);
	void makeMove(int& newX, int& newY) override;
	Turtle* clone(int clonePosX, int clonePosY) const override;
	bool collision(Organism* invader) override;
	~Turtle();
};