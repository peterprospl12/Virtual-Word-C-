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

char Organism::getPrefix() {
	return prefix;
}

string Organism::getName() {
	return name;
}

void Organism::incrementAge() {
    this->age++;
}

void Organism::decrementAge() {
    this->age--;
}
void Organism::setStrength(int newStrength) {
	this->strength = newStrength;
}



void Organism::makeMove(int& newX, int& newY) {
    newX = posX; // aktualna pozycja x zwierzęcia
    newY = posY; // aktualna pozycja y zwierzęcia

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
    currWorld.setOrganism(nullptr, this->posX, this->posY);
	this->posX = newX;
	this->posY = newY;
    currWorld.setOrganism(this, this->posX, this->posY);
}


void Organism::setAge(int newAge) {
	this->age = newAge;
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