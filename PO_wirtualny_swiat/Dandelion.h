#pragma once
#include "Plant.h"
class Plant;

class Dandelion : public Plant
{
public:
	Dandelion(int posX, int posY, World& currWorld);
	void action() override;
	Dandelion* clone(int clonePosX, int clonePosY) const override;
	~Dandelion();
};