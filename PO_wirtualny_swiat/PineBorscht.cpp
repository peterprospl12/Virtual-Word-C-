#include "Plant.h"
#include "PineBorscht.h"
#include "World.h"
#include "Animal.h"

PineBorscht::PineBorscht(int posX, int posY, World& currWorld)
	:Plant(10, PLANT_INITIATIVE, posX, posY, 'P', "PineBorscht", currWorld)
{
}


void PineBorscht::action() {
	int currPosX = this->posX;
	int currPosY = this->posY;
	int PosToKillX, PosToKillY;
	Organism*** currBoard = currWorld.getBoard();
	int moves[8][2] = { {0,-1}, {0,1}, {-1,0}, {1,0}, {-1,-1}, {1,-1}, {-1,1}, {1,1} };

	for (int i = 0; i < 8; i++) {
		PosToKillX = currPosX + moves[i][0];
		PosToKillY = currPosY + moves[i][1];

		if (PosToKillX >= 0 && PosToKillX < currWorld.getBoardSizeX() && PosToKillY >= 0 && PosToKillY < currWorld.getBoardSizeY()) {
			Organism* OrgtoKill = currBoard[PosToKillY][PosToKillX];
			Animal* AnimalToKill = dynamic_cast<Animal*>(OrgtoKill);

			if (AnimalToKill != nullptr) {
				currWorld.getInfoStream() << *this << " has killed " << *currBoard[PosToKillY][PosToKillX] << std::endl;
				currWorld.drawWorld();
				currWorld.removeOrganism(*currBoard[PosToKillY][PosToKillX]);
			}
		}

	}
	this->Plant::action();

}

bool PineBorscht::collision(Organism* invader) {
	currWorld.getInfoStream() << *invader << " has ate " << *this << " and died!" << std::endl;
	currWorld.removeOrganism(*invader);
	return true;
}

PineBorscht* PineBorscht::clone(int clonePosX, int clonePosY) const {
	PineBorscht* cloned = new PineBorscht(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

PineBorscht::~PineBorscht() {
}
