/*
Basic entity is the robot, which is named SuperPac
Ghost will be a subclass of SuperPac, as only one variable is being modified

*/



class SuperPac{
	//more functions will be implemented as time progresses
	char col; //will be used to represent entity as a colored object
	int posX;
	int posY;
	bool hostile;

public:
	SuperPac(int x, int y): col('y'), posX(x), posY(y), hostile(false){}

protected:
	
};

class Ghost : public SuperPac{
	
public:


};