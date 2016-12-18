/*
Contains info about the Pacman, Ghost, Dots, Powerups
*/


class Entity{
	char symb; 
	int posX, posY, pntVal;
	bool eatable;

public:
	Entity(): symb(' '), posX(0), posY(0), pntVal(0), eatable(false){}
	Entity(char s, int x, int y, int pv, bool eat) : symb(s), posX(x), posY(y), pntVal(pv), eatable(eat) {}
	char getSymb()						{ return symb; };
	int getPosX()						{ return posX; };
	int getPosY()						{ return posY; };
	int getPntVal()						{ return pntVal; };
	bool isEatable()					{ return eatable; };

	void setSymbol(char val)			{ symb = val; };
	void setPosX(int val)				{ posX = val;  };
	void setPosY(int val)				{ posY = val;  };
	void setPntVal(int val)				{ pntVal = val;  };
	void setEatable(bool val)			{ eatable = val;  };

};

class Pellet : public Entity{
	
public:
	Pellet() :Entity(){ 
		setSymbol('*');
		setEatable(true);
		setPntVal(10);
	}
	Pellet(int x, int y) :Entity('*', x, y, 10, true){}	
};

class PwrPlt : public Pellet{

};


class SuperPac :public Entity{
public:

};