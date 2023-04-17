#pragma once
#include "Plant.h"
class Plant;

class Guarana : public Plant
{
public:
	Guarana(int posX, int posY, World& currWorld);
	
	bool collision(Organism* invader) override;
	Guarana* clone(int clonePosX, int clonePosY) const override;
	
	~Guarana();
};