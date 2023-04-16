#include "Antelope.h"
#include "World.h"
#include <chrono>
Antelope::Antelope(int posX, int posY, World& currWorld)
	:Animal(4, 4, posX, posY, 'A', "Antelope", currWorld)
{
}


void Antelope::makeMove(int& newX, int& newY) {
    newX = posX; // aktualna pozycja x zwierzêcia
    newY = posY; // aktualna pozycja y zwierzêcia
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    Organism*** currBoard = currWorld.getBoard();

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
    
    // 50% szans na ucieczkê 0 - ucieczka, 1 - walka
    
    if (rand_number == 0) {
        int newX, newY;
        int oldX, oldY;
        oldX = this->posX;
        oldY = this->posY;
        do
        {
            this->Organism::makeMove(newX, newY);
        
        } while (currWorld.getBoard()[newY][newX] != nullptr);
        
        

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