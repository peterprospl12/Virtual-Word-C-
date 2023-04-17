#include <iostream>
#include "World.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Antelope.h"
#include "Turtle.h"
#include "Human.h"
using std::cout;
using std::endl;
using std::cin;


int main() {
	World Galactic(20,20);
	Galactic.performTurn();

	return 0;
}