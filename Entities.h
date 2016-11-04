/*
Basic entity is the robot, which is named SuperPac
Ghost will be a subclass of SuperPac, as only one variable is being modified

*/



class Entity{
	//more functions will be implemented as time progresses
	char symbol; //will be used to represent entity as a symbol
	int posX, posY, pntVal;
	bool eatable;

public:
	Entity(): symbol(' '), posX(0), posY(0), pntVal(0), eatable(false){}


};

class Dot : public Entity{
	
public:
	Dot(int x, int y){
		
	}
};

class PwrDot : public Dot{

};