#pragma once
#include "Animal.h"
class World;
class Animal;

class Antelope : public Animal
{
public:
	Antelope(int posX, int posY, World& currWorld);
	void makeMove(int& newX, int& newY) override;
	bool collision(Organism* invader) override;
	Antelope* clone(int clonePosX, int clonePosY) const override;
	~Antelope();
};