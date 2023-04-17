#pragma once
#include "Animal.h"
class World;
class Animal;

class Sheep : public Animal
{
public:
	Sheep(int posX, int posY, World& currWorld);
	
	Sheep* clone(int clonePosX, int clonePosY) const override;
	
	~Sheep();
};