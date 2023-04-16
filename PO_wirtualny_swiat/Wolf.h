#pragma once
#include "Animal.h"
class World;
class Animal;

class Wolf : public Animal
{
public:
	Wolf(int posX, int posY, World& currWorld);
	Wolf* clone(int clonePosX, int clonePosY) const override;
	~Wolf();
};