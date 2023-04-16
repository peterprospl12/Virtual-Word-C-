#include <chrono>
#include "Organism.h"
#include "World.h"
using std::cout;
Organism::Organism(int strength, int initiative, int posX, int posY, char prefix, string name, World& currWorld)
	:strength(strength), initiative(initiative), posX(posX), posY(posY), prefix(prefix), name(name), currWorld(currWorld)
{

}

void Organism::draw() {
	cout << prefix;
}

int Organism::getPosX() {
	return posX;
}

int Organism::getPosY() {
	return posY;
}

int Organism::getAge() {
    return age;
}

int Organism::getStrength() {
	return strength;
}
int Organism::getInitiative() {
	return initiative;
}

void Organism::incrementAge() {
    this->age++;
}

void Organism::decrementAge() {
    this->age--;
}




void Organism::makeMove(int& newX, int& newY) {
    newX = posX; // aktualna pozycja x zwierzêcia
    newY = posY; // aktualna pozycja y zwierzêcia
    Organism*** currBoard = currWorld.getBoard();
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
                break;
            }
        }
    }
}

void Organism::setNewPosition(int newX, int newY) {
    Organism*** currBoard = currWorld.getBoard();
    currBoard[this->posY][this->posX] = nullptr;
	this->posX = newX;
	this->posY = newY;
    currBoard[this->posY][this->posX] = this;
}


bool Organism::hasBlocked(Organism* invader)
{
    int invaderStrenght = invader->strength;
    int defenderStrenght = this->strength;

    if (invaderStrenght >= defenderStrenght) {
        return false;
    }
    else {
        return true;
    }
}


std::ostream& operator<<(std::ostream& os, const Organism& organism) {
	os << "[" << organism.name << "] " << "Age: " << organism.age;
	return os;
}

Organism::~Organism() {

}