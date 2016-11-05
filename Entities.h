/*
LIST OF ALL ENTITIES:
-GHOSTSES
-SUPERPAC
-DOT
-SUPERDOT
*/



class Entity{
	//more functions will be implemented as time progresses
	char symbol; //will be used to represent entity as a symbol
	int posX, posY, pntVal;
	bool eatable;

public:
	Entity(): symbol(' '), posX(0), posY(0), pntVal(0), eatable(false){}
	Entity(char s, int x, int y, int pv, bool eat) : symbol(s), posX(x), posY(y), pntVal(pv), eatable(eat){}
	char getSymbol()					{ return symbol; };
	int getPosX()						{ return posX; };
	int getPosY()						{ return posY; };
	int getPntVal()						{ return pntVal; };
	bool isEatable()					{ return eatable; };

	void setSymbol(char val)			{ symbol = val;  };
	void setPosX(int val)				{ posX = val;  };
	void setPosY(int val)				{ posY = val;  };
	void setPntVal(int val)				{ pntVal = val;  };
	void setEatable(bool val)			{ eatable = val;  };
};

class Dot : public Entity{
	
public:
	Dot() :Entity(){ 
		setSymbol('*');
		setEatable(true);
		setPntVal(10);
	}
	Dot(int x, int y) :Entity('*', x, y, 10, true){}	
};

class PwrPlt : public Dot{

};


class SuperPac :public Entity{
public:

};