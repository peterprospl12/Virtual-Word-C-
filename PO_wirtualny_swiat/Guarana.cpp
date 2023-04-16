#include "Guarana.h"
#include "Plant.h"
#include "World.h"


Guarana::Guarana(int posX, int posY, World& currWorld)
	:Plant(0, PLANT_INITIATIVE, posX, posY, 'U', "Guarana", currWorld)
{
}

Guarana* Guarana::clone(int clonePosX, int clonePosY) const {
	Guarana* cloned = new Guarana(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

bool Guarana::collision(Organism* invader) {
	invader->setStrength(invader->getStrength() + 3);
	currWorld.getInfoStream() << *this << " has increased " << *invader << "'s strength by 3!" << std::endl;
	return false;
}

Guarana::~Guarana() {
}