/*
Contains info about the Pacman, Ghost, Dots, Powerups
*/
#include <stdlib.h>
#include "coordindex.h"
#include <iostream>

using std::cout;
using std::endl;

class Entity{ //same thing as an empty space
	char symb; 
	int posX, posY, pntVal;
	bool eatable;
public:
	Entity(): symb(' '), posX(0), posY(0), pntVal(0), eatable(true){}
	Entity(int x, int y) : symb(' '), posX(x), posY(y), pntVal(0), eatable(true) {}
	char getSymb()						{ return symb; };
	int getPosX()						{ return posX; };
	int getPosY()						{ return posY; };
	int getPntVal()						{ return pntVal; };
	bool isEatable()					{ return eatable; };

	void setSymb(char val)			{ symb = val; };
	void setPosX(int val)				{ posX = val;  };
	void setPosY(int val)				{ posY = val;  };
	void setPntVal(int val)				{ pntVal = val;  };
	void setEatable(bool val)			{ eatable = val;  };
};

class Unknown : public Entity {
	//to maybe be implemented
};

class Consumable : public Entity {
public:
	Consumable() :Entity() {}
	Consumable(int x, int y) :Entity(x, y) {}
	//virtual void gotEaten(); might implement later, most likely not
};

class Pellet : public Consumable{
	
public:
	Pellet() :Consumable(){ 
		setSymb('*');
		setPntVal(10);
	}

	Pellet(int x, int y) :Consumable(x, y){
		setSymb('*');
		setPntVal(10);
	}	
};

class PwrPlt : public Pellet{

public:
	PwrPlt() :Pellet() {
		setSymb('@');
		setPntVal(50);
	}
	PwrPlt(int x, int y) :Pellet(x, y) {
		setSymb('@');
		setPntVal(50);
	}
};


class Roamer :public Entity {
	char dir;

public:
	Roamer() : Entity(){
		dir = 'n';
	}
	Roamer(int x, int y) : Entity(x, y) {
		dir = 'n';
	}
	char rand_dir();
	char get_dir() { return dir; }
	void set_dir(char a) { dir = a; }
	int advance(int current, char dir);//advances one tile in specified direction, returns the end tile
};

class Pac :public Roamer {
public:
	Pac() :Roamer() {
		setSymb('P');
	}
	Pac(int x, int y) :Roamer(x, y) {}

};

class Ghost :public Roamer {

public:
	Ghost() :Roamer() {
		setSymb('G');
		setPntVal(200);
	}
	Ghost(int x, int y) :Roamer(x, y) {}
	int move(int currentpos, int targetpos, bool[22]); //moves one tile towards target tile, uses an array of intersection tiles for speed
	void move_scatter(int cornerpos); //the ghosts retreat to a corner of the map
	void move_chase(int pacpos);
	void move_frightened();
};