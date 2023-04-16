#include "Plant.h"
#include "Dandelion.h"

const int CHANCES_TO_MULTIPLY = 3;

Dandelion::Dandelion(int posX, int posY, World& currWorld)
	:Plant(0, PLANT_INITIATIVE, posX, posY, 'D', "Dandelion", currWorld)
{
}


void Dandelion::action() {
	for (int i = 0; i < CHANCES_TO_MULTIPLY; i++) {
		this->Plant::action();
	}

}


Dandelion* Dandelion::clone(int clonePosX, int clonePosY) const {
	Dandelion* cloned = new Dandelion(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}