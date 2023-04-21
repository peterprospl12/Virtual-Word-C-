#include "Fox.h"
#include "World.h"
#include <chrono>

const int FOX_STRENGTH = 3;
const int FOX_INITIATIVE = 7;


Fox::Fox(int posX, int posY, World& currWorld)
	:Animal(FOX_STRENGTH, FOX_INITIATIVE, posX, posY, 'F', "Fox", currWorld)
{
}

Fox* Fox::clone(int clonePosX, int clonePosY) const {
	Fox* cloned = new Fox(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

void Fox::makeMove(int& newX, int& newY) {
    newX = posX;
    newY = posY;
    int toDelete = 0;
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    int moves[8][2] = { {0,-1}, {0,1}, {-1,0}, {1,0}, {-1,-1}, {1,-1}, {-1,1}, {1,1} };

    while (true) {
        int rand_number = (rand() % 8); 

        int dx = moves[rand_number][0];
        int dy = moves[rand_number][1];


        if (newX + dx >= 0 && newX + dx < currWorld.getBoardSizeX() &&
            newY + dy >= 0 && newY + dy < currWorld.getBoardSizeY()) {
            newX += dx;
            newY += dy;

            if (newX != posX || newY != posY) {
                if (currWorld.getOrganism(newX, newY) == nullptr) {
                    break;
                }
                else {
                    if (currWorld.getOrganism(newX, newY)->getStrength() > this->strength) {
                        continue;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}

Fox::~Fox()
{
}