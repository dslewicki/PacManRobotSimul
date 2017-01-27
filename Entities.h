

/*
Contains info about the Pacman, Ghost, Dots, Powerups
*/


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
	//virtual int gotEaten(); decided aganist making it abstract, as I was planning to treat the base entity as an empty tile
};

class Unknown : public Entity {
	//to maybe be implemented
};

class Consumable : public Entity {
public:
	Consumable() :Entity() {}

	Consumable(int x, int y) :Entity(x, y) {}

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
	friend class Map;
	//Map memory; //robot/ghosts personal memory of the map
public:
	//map size to construct the memory map was hardcoded, sorry about that
	Roamer() : Entity(){}
	Roamer(int x, int y) : Entity(x, y) {}

	void move();
    void look();
	//Map getMem() { return memory; };
};

class Pac :public Roamer {
public:
	Pac() :Roamer() {
		setSymb('$');
	}
	Pac(int x, int y) :Roamer(x, y) {}

};