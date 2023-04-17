#pragma once
#include "Plant.h"
class Plant;

class PineBorscht : public Plant
{
public:
	PineBorscht(int posX, int posY, World& currWorld);
	
	void action() override;
	bool collision(Organism* invader) override;
	PineBorscht* clone(int clonePosX, int clonePosY) const override;
	
	~PineBorscht();
};