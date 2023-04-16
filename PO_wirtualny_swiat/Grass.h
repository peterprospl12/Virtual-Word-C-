#pragma once
#include "Plant.h"
class Plant;

class Grass : public Plant
{
public:
	Grass(int posX, int posY, World& currWorld);
	Grass* clone(int clonePosX, int clonePosY) const override;
};