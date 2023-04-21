#include "Human.h"
#include "World.h"
#include <conio.h>

const int HUMAN_STRENGTH = 5;
const int HUMAN_INITIATIVE = 4;

const int LEFT_ARROW = 75;
const int RIGHT_ARROW = 77;
const int UP_ARROW = 72;
const int DOWN_ARROW = 80; 

Human::Human(int posX, int posY, World& currWorld)
	:Animal(HUMAN_STRENGTH, HUMAN_INITIATIVE, posX, posY, 'H', "Human", currWorld)
{
}

void Human::makeMove(int& newX, int& newY) {
	newX = this->posX;
	newY = this->posY;

    currWorld.drawWorld();
    int key = 0;
    while (true)
    {
        key = 0;

        switch ((key = _getch())) {
        case UP_ARROW:
            if (newY >= 1) {
                newY--;
            }
            break;

        case DOWN_ARROW:
            if (newY + 1 < currWorld.getBoardSizeY()) {
                newY++;
            }
            break;

        case LEFT_ARROW:
            if (newX >= 1) {
                newX--;
            }
            break;

        case RIGHT_ARROW:
            if (newX + 1 < currWorld.getBoardSizeX()) {
                newX++;
            }
            break;
        case 'T':
        case 't':
            if (skillCD == 0) {
				skillUsed = true;
				skillCD = 11;
				
				currWorld.getInfoStream() << *this << " used his special skill!" << std::endl;
			}
            break;
        case 'S':
        case 's':
            currWorld.makeSave();
            break;
        case 'L':
        case 'l':
            currWorld.loadSave();
            newX = this->posX;
            newY = this->posY;
            return;
        }
        if (newX != posX || newY != posY) {
            break;
        }
    }

    if (skillUsed) {
		skillCD--;
        if (skillCD < 6) {
            if (skillCD == 0) {
                skillUsed = false;
            }
		}
        else {
            currWorld.getInfoStream() << *this << " skill is activated for " << skillCD-5 << " turns!" << std::endl;
        }
    }


}


bool Human::collision(Organism* invader) {
    if (!skillUsed) {
        return false;
    }
    int currPosX = this->posX;
    int currPosY = this->posY;
    int PosToSkipX = -10;
    int PosToSkipY = -10;
    int PosToKillX, PosToKillY;
    int moves[8][2] = { {0,-1}, {0,1}, {-1,0}, {1,0}, {-1,-1}, {1,-1}, {-1,1}, {1,1} };


    for (int i = 0; i < 8; i++) {
        PosToKillX = currPosX + moves[i][0];
		PosToKillY = currPosY + moves[i][1];

        if (PosToKillX == PosToSkipX && PosToKillY == PosToSkipY) {
            continue;
        }

        if (PosToKillX >= 0 && PosToKillX < currWorld.getBoardSizeX() && PosToKillY >= 0 && PosToKillY < currWorld.getBoardSizeY()) {
            if (currWorld.getOrganism(PosToKillX, PosToKillY) != nullptr) {
                currWorld.getInfoStream() << *this << " has killed " << *currWorld.getOrganism(PosToKillX, PosToKillY) << " with his skill!" << std::endl;
				currWorld.removeOrganism(*currWorld.getOrganism(PosToKillX, PosToKillY));
			}
		}

    }
    return true;

}






int Human::getCooldown() {
	return skillCD;
}

bool Human::getSkillUsed() {
    return skillUsed;
}

void Human::setCooldown(int newCD) {
	this->skillCD = newCD;
}

void Human::setSkillUsed(bool newSkillUsed) {
	this->skillUsed = newSkillUsed;
}

Human* Human::clone(int clonePosX, int clonePosY) const {
	return nullptr;
}

Human::~Human() {}