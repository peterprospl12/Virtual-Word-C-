#include "Turtle.h"
#include "World.h"
#include <chrono>

const int TURTLE_STRENGTH = 2;
const int TURTLE_INITIATIVE = 1;

Turtle::Turtle(int posX, int posY, World& currWorld)
	:Animal(TURTLE_STRENGTH, TURTLE_INITIATIVE, posX, posY, 'T', "Turtle", currWorld)
{
}

void Turtle::makeMove(int& newX, int& newY) {
    newX = posX;
    newY = posY;
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    int rand_number = (rand() % 4) + 1;
    if (rand_number != 1) {
        return;
	}        
    this->Organism::makeMove(newX, newY);
}

bool Turtle::collision(Organism* attacker) {
    if (attacker->getStrength() < 5) {
        currWorld.getInfoStream() << *this << " has defended itself from " << *attacker << " with shell!" << std::endl;
        return true;
	}
    else {
        return false;
	}
}   

Turtle* Turtle::clone(int clonePosX, int clonePosY) const {
	Turtle* cloned = new Turtle(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

Turtle::~Turtle() {
}