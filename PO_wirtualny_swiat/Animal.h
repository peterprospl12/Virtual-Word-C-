#pragma once
#include <iostream>
#include "Organism.h"
class World;

class Animal : public Organism
{
public:
	Animal(int strength, int initiative, int posX, int posY, char prefix, string name, World& currWorld);
    void action() override;
	bool checkMultiply(Animal* defender);
	bool collision(Organism* invader) override;
	virtual Animal* clone(int clonePosX, int clonePosY) const = 0;
};