
class Entity{
	char clr; 
	int posX, posY, pntVal;
	bool eatable;

public:
	Entity(): clr(' '), posX(0), posY(0), pntVal(0), eatable(false){}
	Entity(char s, int x, int y, int pv, bool eat) : clr(s), posX(x), posY(y), pntVal(pv), eatable(eat) {}
	char getClr()						{ return clr; };
	int getPosX()						{ return posX; };
	int getPosY()						{ return posY; };
	int getPntVal()						{ return pntVal; };
	bool isEatable()					{ return eatable; };

	void setSymbol(char val)			{ clr = val; };
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