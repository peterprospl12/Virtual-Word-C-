#include "Wolfberries.h"
#include "Plant.h"
#include "World.h"


Wolfberries::Wolfberries(int posX, int posY, World& currWorld)
	:Plant(99, PLANT_INITIATIVE, posX, posY, 'B', "Wolfberries", currWorld)
{
}

Wolfberries* Wolfberries::clone(int clonePosX, int clonePosY) const {
	Wolfberries* cloned = new Wolfberries(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

bool Wolfberries::collision(Organism* invader) {
	currWorld.getInfoStream() << *invader << " has ate " << *this << " and died!" << std::endl;
	currWorld.removeOrganism(*invader);
	return true;
}

Wolfberries::~Wolfberries() {
}