#pragma once

#include <iostream>
#include "Organism.h"
class World;

const int PLANT_INITIATIVE = 0;

class Plant : public Organism
{
public:
	Plant(int strength, int initiative, int posX, int posY, char prefix, string name, World& currWorld);
	
	void action() override;
	bool collision(Organism* invader) override;
	
	virtual Plant* clone(int clonePosX, int clonePosY) const = 0;
	
	~Plant();

};	