#include "Antelope.h"
#include "World.h"
#include <chrono>


const int ANTELOPE_STRENGTH = 4;
const int ANTELOPE_INITIATIVE = 4;

Antelope::Antelope(int posX, int posY, World& currWorld)
	:Animal(ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, posX, posY, 'A', "Antelope", currWorld)
{
}


void Antelope::makeMove(int& newX, int& newY) {
    newX = posX; 
    newY = posY; 
    srand(std::chrono::system_clock::now().time_since_epoch().count());

    int moves[16][2] = {
        {-2, -2}, {-2, 0}, {-2, 2}, {0, -2}, {0, 2}, {2, -2}, {2, 0}, {2, 2},
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };
    while (true) {
        int rand_number = rand() % 16;
        
        int dx = moves[rand_number][0];
        int dy = moves[rand_number][1];

        if (newX + dx >= 0 && newX + dx < currWorld.getBoardSizeX() &&
            newY + dy >= 0 && newY + dy < currWorld.getBoardSizeY()) {
            newX += dx;
            newY += dy;

            if (newX != posX || newY != posY) {
                break;
            }
        }
    }
}

bool Antelope::collision(Organism* attacker) {
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    int rand_number = rand() % 2;
    int counter = 0;
    // 50% chance to escape 0 - escape, 1 - fight
    
    if (rand_number == 0) {
        int newX, newY;
        int oldX, oldY;
        oldX = this->posX;
        oldY = this->posY;
        do
        {
            this->Organism::makeMove(newX, newY);
            counter++;
            if (counter > 100) {
				return false;
			}
        } while (currWorld.getOrganism(newX, newY) != nullptr);
        
        

        this->setNewPosition(newX, newY);
        attacker->setNewPosition(oldX, oldY);
        currWorld.getInfoStream() << *this << " escaped from " << *attacker << " and moved to (" << newX << ", " << newY << ")" << std::endl;

        return true;
    }
    else {
        return false;
    }
}


Antelope* Antelope::clone(int clonePosX, int clonePosY) const {
	Antelope* cloned = new Antelope(clonePosX, clonePosY, this->currWorld);
	cloned->decrementAge();
	return cloned;
}

Antelope::~Antelope()
{
}