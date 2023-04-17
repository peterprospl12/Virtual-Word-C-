#pragma once
#include "Animal.h"
class World;
class Animal;

class Fox : public Animal
{
public:
	Fox(int posX, int posY, World& currWorld);
	
	void makeMove(int& newX, int& newY) override;
	Fox* clone(int clonePosX, int clonePosY) const override;
	
	~Fox();
};