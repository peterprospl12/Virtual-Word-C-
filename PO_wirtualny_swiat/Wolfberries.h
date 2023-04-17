#pragma once
#include "Plant.h"
class Plant;

class Wolfberries : public Plant
{
public:
	Wolfberries(int posX, int posY, World& currWorld);
	
	bool collision(Organism* invader) override;
	Wolfberries* clone(int clonePosX, int clonePosY) const override;
	
	~Wolfberries();
};