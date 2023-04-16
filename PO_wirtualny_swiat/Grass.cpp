#include "Plant.h"
#include "Grass.h"

Grass::Grass(int posX, int posY, World& currWorld)
	:Plant(0, PLANT_INITIATIVE, posX, posY, 'G', "Grass", currWorld)
{
}

Grass* Grass::clone(int clonePosX, int clonePosY) const {
	Grass* cloned = new Grass(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}