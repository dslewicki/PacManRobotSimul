#include <vector>
#include "Entities.h"
#include <iterator>
/*
Graph will be represented as an adjacency list,
using std::vector, and possibly std::map, depending on
further progress.

Will be using intializer lists with constructor for faster initialization (or so I remember).  For those who aren't familiar with the syntax,

public classConstructor(){		is the same as			public classConstructor():this(that){}
this=that;						-------------->
}



*/

using std::vector;


class Vertex{
	SuperPac *val;//set to null if there exists no entity in this space
	char idnty;  //used for testing graph
	int xPos;
	int yPos;

public:
	//Vertex(): val(NULL), xPos(0), yPos(0){}
		//neighbors=new vector<Vertex>

	//called during build
	Vertex(int x) : val(NULL), xPos(x){
		idnty = 65 + x;
	}

	~Vertex(){
		delete val;
	}

	char getIdnty(){
		return idnty;
	}

	string& operator*(){ return getIdnty(); }
	//MIGHT NOT BE NECESSARY: Vertex(int x, int y) : val(NULL), xPos(x), yPos(y){}
};

class Graph{
	int totalVertices; //number of vertices, should be 100
	int keynum;  //square root of the vertices, will be used extensively
	vector<vector<Vertex*>> vertices;
	//vector<vector<Vertex*>>::iterator it;
	vector<Vertex*>::iterator iter;

public:
	//initializes the graph, but does not connect the edges
	Graph(int numOfVertices):totalVertices(numOfVertices), keynum(sqrt(numOfVertices)){
		for (int i = 0; i < numOfVertices; i++)
			vertices.at(i).push_back(new Vertex(i));
	} 

	/*~Graph(){
		for (int i = 0; i < totalVertices; i++){
			iter = vertices.at(i).begin();
			while (iter != NULL){
				delete *iter;

			}
			vertices.at(i).clear();
		}
	}*/

	void build(); //initialize the maze connections  NOTE: I didn't include this in the constructor incase I wanted a blank graph
	void addNeighbors(int);  //adds the four assumed neighbors
	void addEdge(int, Vertex*); //int is destination index

	void removeEdge(int, Vertex*);  //given a vertex index and a vertex to be removed
	void BFS();  //breadth-first search, might be adjusted to accommodate for more general distance appromixation
	void printGraph();//prints out the graph in console
	std::string printNeighbors(int);//prints out a vertex's neighbors  (decided against overloading <<, as that would been cancer)
};