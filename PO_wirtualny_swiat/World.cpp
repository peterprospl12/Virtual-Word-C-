#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
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
#include "Guarana.h"
#include "Wolfberries.h"
#include "PineBorscht.h"

using std::cout;
using std::endl;
using std::cin;

const int studentInfoPosX = 10;
const int studentInfoPosY = 0;
const int boardPosX = 0;
const int boardPosY = 5;


void World::performTurn() {

	this->addOrganism(new Grass(9, 9, *this));
	this->addOrganism(new Dandelion(1, 0, *this));
	this->addOrganism(new PineBorscht(7, 2, *this));
	this->addOrganism(new Antelope(7, 1, *this));
	this->addOrganism(new Antelope(6, 1, *this));
	this->addOrganism(new Wolf(6, 10, *this));
	this->addOrganism(new Turtle(10, 3, *this));
	this->addOrganism(new Sheep(8, 1, *this));
	this->addOrganism(new Sheep(8, 2, *this));
	this->addOrganism(new Fox(6, 13, *this));
	this->addOrganism(new Fox(2, 13, *this));
	this->addOrganism(new Human(10, 10, *this));
	this->addOrganism(new Wolf(16, 16, *this));
	this->addOrganism(new Fox(7, 9, *this));
	this->addOrganism(new Antelope(7, 7, *this));
	this->addOrganism(new Wolfberries(13, 2, *this));
	this->addOrganism(new Guarana(5, 15, *this));
	this->addOrganism(new Guarana(15, 5, *this));


	

	while (humanAlive) {
		this->sortOrganisms();
		for (int i = 0; i < organisms.size(); i++) {
			if (!humanAlive)
			{
				break;
			}

			if (gameSaved) {
				continue;
			}

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
		gameSaved = false;
	}
	this->drawWorld();
}

void World::addOrganism(Organism* organism) {
	if (dynamic_cast<Human*>(organism) != nullptr)
	{
		humanAlive = true;
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
		humanAlive = false;
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



World::World(int boardSizeX, int boardSizeY)
	:boardSizeX(boardSizeX), boardSizeY(boardSizeY)
{
	board = new Organism**[boardSizeY];
	for (int i = 0; i < boardSizeY; i++) {
		board[i] = new Organism*[boardSizeX];
		for (int j = 0; j < boardSizeX; j++) {
			board[i][j] = nullptr; 
		}
	}
	
}

void World::humanDied() {
	humanAlive = false;
}

void World::drawInfo() {
	int infoPosX = boardPosX + getBoardSizeX()*2 + 10;
	int infoPosY = 0;	
	int size = organisms.size();
	int infoX = 50;
	int infoY = 1;
	//for (int i = 0; i < size; i++) {
	//	gotoxy(infoPosX, infoPosY+i);
	//	cout << *organisms[i] << endl;
	//}
	std::string line;
	std::istringstream iss(infoStream.str());
	while (std::getline(iss, line)) {
		gotoxy(infoX, infoY);
		std::cout << line << std::endl;
		infoY++;
	}
	infoStream.str("");
	infoY = 1;

}


void World::drawWorld() {
	system("cls");
	gotoxy(studentInfoPosX, studentInfoPosY);
	cout << "[ Piotr Sulewski 19254 ] " << endl;


	for (int i = -1; i < boardSizeY+1; i++) {
		for (int j = -1; j < boardSizeX+1; j++) {
			gotoxy(boardPosX + (j * 2) + 2, boardPosY + i + 1);
			if (j == -1) {
				cout << "# ";
			}
			else if (j == boardSizeX) {
				cout << "#";
			}
			else if (i == -1 || i == boardSizeY) {
				cout << "# ";
			}
			else {
				if (board[i][j] == nullptr) {
					cout << ".";
				}
				else {
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					if (board[i][j]->getPrefix() == 'H') {
						SetConsoleTextAttribute(hConsole,  FOREGROUND_GREEN);
					}
					board[i][j]->draw();
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


				}
				cout << " ";
			}
		}
		gotoxy(boardPosX + 2, boardPosY + i + 1);
	}

	drawInfo();
}

int World::getBoardSizeX() {
	return boardSizeX;
}

int World::getBoardSizeY() {
	return boardSizeY;
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


void World::makeSave() {
	string filename;
	system("cls");
	
	cout << "Input filename: ";
	cin >> filename;	
	
	filename = filename + ".txt";
	std::ofstream saveFile;
	
	saveFile.open(filename);
	saveFile << boardSizeX << " " << boardSizeY << endl;
	
	int size = organisms.size();
	
	for (int i = 0; i < size; i++) {
		saveFile << organisms[i]->getPrefix() << " ";
		Human* isHuman = dynamic_cast<Human*>(organisms[i]);
		if (isHuman != nullptr) {
			saveFile << isHuman->getCooldown() << " " << isHuman->getSkillUsed() << " ";
		}
		saveFile << organisms[i]->getStrength() << " " << organisms[i]->getPosX() << " " 
			<< organisms[i]->getPosY() << " " << organisms[i]->getAge() << " "  << endl;
			
	}
	
	saveFile.close();
	drawWorld();
}


void World::loadSave() {
	string filename;
	int sizeX, sizeY;
	std::ifstream saveFile;


	system("cls");
	cout << "Input filename: ";
	
	cin >> filename;
	
	drawWorld();
	
	filename = filename + ".txt";
	
	
	saveFile.open(filename);
	
	if (!saveFile.is_open()) {
		return;
	}
	
	saveFile >> sizeX >> sizeY;
	
	for (int i = 0; i < boardSizeY; i++) {
		for (int j = 0; j < boardSizeX; j++) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
	
	this->boardSizeX = sizeX;
	this->boardSizeY = sizeY;
	
	board = new Organism**[boardSizeY];
	for (int i = 0; i < boardSizeY; i++) {
		board[i] = new Organism*[boardSizeX];
		for (int j = 0; j < boardSizeX; j++) {
			board[i][j] = nullptr; 
		}
	}

	organisms.clear();
	
	int cooldown, skillUsed, strength, posX, posY, age;
	char prefix;

	while (saveFile >> prefix) {
		if (prefix == 'H') {
			saveFile >> cooldown >> skillUsed;
		}
		saveFile >> strength >> posX >> posY >> age;
		if (prefix == 'H') {
			Human* human = new Human(posX, posY, *this);
			human->setCooldown(cooldown);
			human->setSkillUsed(skillUsed);
			human->setAge(age);
			this->addOrganism(human);
		}
		else if (prefix == 'A') {
			Antelope* antelope = new Antelope(posX, posY, *this);
			antelope->setAge(age);
			this->addOrganism(antelope);
		}
		else if (prefix == 'F') {
			Fox* fox = new Fox(posX, posY, *this);
			fox->setAge(age);
			this->addOrganism(fox);
		}
		else if (prefix == 'S') {
			Sheep* sheep = new Sheep(posX, posY, *this);
			sheep->setAge(age);
			this->addOrganism(sheep);
		}
		else if (prefix == 'T') {
			Turtle* turtle = new Turtle(posX, posY, *this);
			turtle->setAge(age);
			this->addOrganism(turtle);
		}
		else if (prefix == 'W') {
			Wolf* wolf = new Wolf(posX, posY, *this);
			wolf->setAge(age);
			this->addOrganism(wolf);
		}
		else if (prefix == 'D') {
			Dandelion* dandelion = new Dandelion(posX, posY, *this);
			dandelion->setAge(age);
			this->addOrganism(dandelion);
		}
		else if (prefix == 'G') {
			Grass* grass = new Grass(posX, posY, *this);
			grass->setAge(age);
			this->addOrganism(grass);
		}
		else if (prefix == 'U') {
			Guarana* guarana = new Guarana(posX, posY, *this);
			guarana->setAge(age);
			this->addOrganism(guarana);
		}
		else if (prefix == 'P') {
			PineBorscht* pineBorscht = new PineBorscht(posX, posY, *this);
			pineBorscht->setAge(age);
			this->addOrganism(pineBorscht);
		}
		else if (prefix == 'B') {
			Wolfberries* wolfberries = new Wolfberries(posX, posY, *this);
			wolfberries->setAge(age);
			this->addOrganism(wolfberries);
		}
	}
	
	this->gameSaved = true;
	saveFile.close();
	drawWorld();

}



World::~World() {
	for (int i = 0; i < boardSizeY; i++) {
		for (int j = 0; j < boardSizeX; j++) {
			delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}
