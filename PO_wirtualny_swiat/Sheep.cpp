#include "Sheep.h"
#include "World.h"

Sheep::Sheep(int posX, int posY, World& currWorld)
	:Animal(4, 4, posX, posY, 'S', "Sheep", currWorld)
{
}

Sheep* Sheep::clone(int clonePosX, int clonePosY) const {
	Sheep* cloned = new Sheep(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

Sheep::~Sheep() {

}