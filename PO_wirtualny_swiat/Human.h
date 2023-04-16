#pragma once
#include "Animal.h"
class World;
class Animal;

class Human : public Animal
{
private:
	int skillCD = 0;
	bool skillUsed = false;
public:
	Human(int posX, int posY, World& currWorld);
	void makeMove(int &newX, int& newY) override;
	Human* clone(int clonePosX, int clonePosY) const override;
	bool collision(Organism* invader) override;
	int getCooldown();
};