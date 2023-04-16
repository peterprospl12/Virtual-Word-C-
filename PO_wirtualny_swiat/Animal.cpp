#include <iostream>
#include "Organism.h"
#include <time.h>
#include "Animal.h"
#include "World.h"
#include <sstream>
#include <chrono>
Animal::Animal(int strength, int initiative, int posX, int posY, char prefix, string name, World& currWorld)
    :Organism(strength, initiative, posX, posY, prefix, name, currWorld)
{
}

void Animal::action() {
    int newX, newY;
    Organism*** currBoard = currWorld.getBoard();
    std::stringstream& infoStream = currWorld.getInfoStream();

    this->makeMove(newX, newY);
   
    if (newX == this->posX && newY == this->posY) {
		return;
	}
    

    if (currBoard[newY][newX] != nullptr) {
        Organism* defender = currBoard[newY][newX];
        Animal* animalDefender = dynamic_cast<Animal*>(defender);
        int toDelete = 0;
        if (this->checkMultiply(animalDefender)) {
            return;
        }

        if (defender->collision(this)) {
            return;
        }


        if (defender->hasBlocked(this)) {
            infoStream << *defender << " blocked and killed " << *this << std::endl;
            currWorld.removeOrganism(*this);
        }
        else {
            infoStream << *this << " killed " << *defender << " and moved to (" << newX << "," << newY << ")" << std::endl;
            currWorld.removeOrganism(*currBoard[newY][newX]);
            this->setNewPosition(newX, newY);
        }

    }
    else {
        infoStream << *this << " moved to (" << newX << "," << newY << ")" << " from (" << this->posX << "," << this->posY << ")" << std::endl;
        this->setNewPosition(newX, newY);
    }
}


bool Animal::checkMultiply(Animal* defender) {
    Animal 
    if (typeid(*this) == typeid(*defender)) {
        int newX, newY;
        int tryCount = 0;
        Organism*** currBoard = currWorld.getBoard();
        srand(std::chrono::system_clock::now().time_since_epoch().count());
        do {
            int rand_number = (rand() % 2) + 1;
            if (rand_number == 1) {
                defender->Organism::makeMove(newX, newY);
            }
            else {
                this->Organism::makeMove(newX, newY);
            }
            tryCount++;
        } while (currBoard[newY][newX] != nullptr && tryCount < 30);
        if (tryCount >= 30) {
            return false;
        }
        Animal* kid = this->clone(newX, newY);
        currWorld.addOrganism(kid);
        currWorld.getInfoStream() << *kid << " was born on (" << kid->getPosX() << "," << kid->getPosY() << ")" << std::endl;
        return true;
    }
    return false;

}


bool Animal::collision(Organism* invader) {
    return false;
}

