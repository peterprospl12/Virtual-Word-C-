#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <algorithm>
#include "World.h"
#include "Organism.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Antelope.h"
#include "Turtle.h"
#include "Human.h"
#include "Dandelion.h"
#include "Grass.h"
using std::cout;
using std::endl;
using std::cin;

const int studentInfoPosX = 10;
const int studentInfoPosY = 0;
const int boardPosX = 0;
const int boardPosY = 5;


void World::performTurn() {
	int a;

	this->addOrganism(new Grass(9, 9, *this));
	this->addOrganism(new Dandelion(1, 0, *this));
	//this->addOrganism(new Wolf(4, 0, *this));
	//this->addOrganism(new Wolf(5, 0, *this));
	this->addOrganism(new Human(1, 1, *this));
	//this->addOrganism(new Wolf(4, 4, *this));
	//this->addOrganism(new Fox(4, 0, *this));
	//this->addOrganism(new Antelope(2, 0, *this));

	
	while (isHumanAlive) {
		this->sortOrganisms();
		for (int i = 0; i < organisms.size(); i++) {
			Organism* currOrg = organisms[i];
			if (currOrg->getAge() > 0) {
				currOrg->action();
				currOrg->incrementAge();
			}
			else
			{
				currOrg->incrementAge();
			}
		}
	}
	this->drawWorld();
}

void World::addOrganism(Organism* organism) {
	if (dynamic_cast<Human*>(organism) != nullptr)
	{
		isHumanAlive = true;
	}
	organisms.emplace_back(organism);
	board[organism->getPosY()][organism->getPosX()] = organism;
}

void World::sortOrganisms() {
	int size = organisms.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (organisms[j]->getInitiative() < organisms[j + 1]->getInitiative()) {
				std::swap(organisms[j], organisms[j + 1]);
			}
			else if (organisms[j]->getInitiative() == organisms[j + 1]->getInitiative()) {
				if (organisms[j]->getAge() < organisms[j + 1]->getAge()) {
					std::swap(organisms[j], organisms[j + 1]);
				}
			}
		}
	}
}	




void World::removeOrganism(Organism& removedOrganism) {
	if (dynamic_cast<Human*>(&removedOrganism) != nullptr)
	{
		isHumanAlive = false;
	}

	std::vector<Organism*>::iterator it = std::find(organisms.begin(), organisms.end(), &removedOrganism);
	if (it != organisms.end()) {
		organisms.erase(it);
	}
	int delPosX = removedOrganism.getPosX();
	int delPosY = removedOrganism.getPosY();
	board[delPosY][delPosX] = nullptr;
	delete &removedOrganism;

}



World::World(int BoardSizeX, int BoardSizeY)
	:BoardSizeX(BoardSizeX), BoardSizeY(BoardSizeY)
{
	board = new Organism**[BoardSizeX];
	for (int i = 0; i < BoardSizeX; i++) {
		board[i] = new Organism*[BoardSizeY];
		for (int j = 0; j < BoardSizeY; j++) {
			board[i][j] = nullptr; 
		}
	}
	
}

void World::humanDied() {
	isHumanAlive = false;
}

void World::drawInfo() {
	int infoPosX = boardPosX + getBoardSizeX()*2 + 10;
	int infoPosY = 0;	
	int size = organisms.size();
	int infoX = 50;
	int infoY = 1;
	for (int i = 0; i < size; i++) {
		gotoxy(infoPosX, infoPosY+i);
		cout << *organisms[i] << endl;
	}
	std::string line;
	std::istringstream iss(infoStream.str());
	while (std::getline(iss, line)) {
		gotoxy(infoX, infoY); // ustawienie pozycji kursora
		std::cout << line << std::endl;
		infoY++; // przesuniêcie pozycji kursora
	}
	infoStream.str(""); // wyczyszczenie zawartoœci infoStream
	infoY = 1;

}


void World::drawWorld() {
	system("cls");
	gotoxy(studentInfoPosX, studentInfoPosY);
	cout << "Piotr Sulewski 19254" << endl;


	for (int i = -1; i < BoardSizeX+1; i++) {
		for (int j = -1; j < BoardSizeY+1; j++) {
			gotoxy(boardPosX + (j * 2) + 2, boardPosY + i + 1);
			if (j == -1) {
				cout << "# ";
			}
			else if (j == BoardSizeY) {
				cout << "#";
			}
			else if (i == -1 || i == BoardSizeX) {
				cout << "# ";
			}
			else {
				if (board[i][j] == nullptr) {
					cout << ".";
				}
				else {
					board[i][j]->draw();
				}
				cout << " ";
			}
		}
		gotoxy(boardPosX + 2, boardPosY + i + 1);
	}

	drawInfo();
}

int World::getBoardSizeX() {
	return BoardSizeX;
}

int World::getBoardSizeY() {
	return BoardSizeY;
}

Organism*** World::getBoard() {
	return board;
}

stringstream& World::getInfoStream() {
	return infoStream;
}


void World::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



World::~World() {
	for (int i = 0; i < BoardSizeX; i++) {
		for (int j = 0; j < BoardSizeY; j++) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}
