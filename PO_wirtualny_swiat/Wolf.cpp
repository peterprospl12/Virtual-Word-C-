#include "Wolf.h"
#include "World.h"

const int WOLF_STRENGTH = 9;
const int WOLF_INITIATIVE = 5;

Wolf::Wolf(int posX, int posY, World& currWorld)
	:Animal(WOLF_STRENGTH, WOLF_INITIATIVE, posX, posY, 'W', "Wolf", currWorld)
{
}

Wolf* Wolf::clone(int clonePosX, int clonePosY) const {
	Wolf* cloned = new Wolf(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

Wolf::~Wolf() {
}