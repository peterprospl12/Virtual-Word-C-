#include "Wolf.h"
#include "World.h"

Wolf::Wolf(int posX, int posY, World& currWorld)
	:Animal(9, 5, posX, posY, 'W', "Wolf", currWorld)
{
}

Wolf* Wolf::clone(int clonePosX, int clonePosY) const {
	Wolf* cloned = new Wolf(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

Wolf::~Wolf() {
}