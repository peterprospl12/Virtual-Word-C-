#include "Sheep.h"
#include "World.h"

const int SHEEP_STRENGTH = 4;
const int SHEEP_INITIATIVE = 4;

Sheep::Sheep(int posX, int posY, World& currWorld)
	:Animal(SHEEP_STRENGTH, SHEEP_INITIATIVE, posX, posY, 'S', "Sheep", currWorld)
{
}

Sheep* Sheep::clone(int clonePosX, int clonePosY) const {
	Sheep* cloned = new Sheep(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

Sheep::~Sheep() {

}