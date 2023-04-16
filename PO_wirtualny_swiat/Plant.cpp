#include <iostream>
#include <chrono>
#include "Plant.h"
#include "World.h"

Plant::Plant(int strength, int initiative, int posX, int posY, char prefix, string name, World& currWorld)
    :Organism(strength, initiative, posX, posY, prefix, name, currWorld)
{
}


bool Plant::collision(Organism* invader) {
    return false;
}


void Plant::action() {
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	int moves[8][2] = { {0,-1}, {0,1}, {-1,0}, {1,0}, {-1,-1}, {1,-1}, {-1,1}, {1,1} };

	int rand_number = rand() % 10 + 1;

	if (rand_number == 2) {
        int newX, newY;
        int tryCount = 0;
        Organism*** currBoard = currWorld.getBoard();
        srand(std::chrono::system_clock::now().time_since_epoch().count());
        do {
            this->Organism::makeMove(newX, newY);
            tryCount++;
        } while (currBoard[newY][newX] != nullptr && tryCount < 30);
        if (tryCount >= 30) {
            return;
        }
        Plant* kid = this->clone(newX, newY);
        currWorld.addOrganism(kid);
        currWorld.getInfoStream() << *kid << " has multiplied on (" << kid->getPosX() << "," << kid->getPosY() << ")" << std::endl;

	}
	else {
		return;
	}


}

Plant::~Plant()
{
}