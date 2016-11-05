#include "Entities.h"
#include <vector>
#include <iterator>
#include <string>
//Gl and GLFW are used for drawing nice things
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
Graph is used to keep track of all possible connections, or, what the maze effectively looks like, and will be used to 
figure out the most efficient path.

Graph will be represented as an adjacency list,
in this case, as a vector of vector<Vertex*>, where each Vertex contains an entity(or not), and an integer value used for testing


Will be using intializer lists with constructor for faster initialization (or so I remember).  For those who aren't familiar with the syntax,

public classConstructor(){		is the same as			public classConstructor():this(that){}
this=that;						-------------->
}
*/

using std::vector;
using std::string;
/*****IMPORTANT******IMPORTANT******IMPORTANT******IMPORTANT******

I refer to the Vertex object as "tile".  Whenever "tile" is mentioned,
it is the equivalent of me saying "Vertex"

*****IMPORTANT******IMPORTANT******IMPORTANT******IMPORTANT******/


class Vertex{
	Entity *val;//set to null if there exists no entity in this space
	int idnty;  //used for testing graph

public:
	Vertex(int x) : val(NULL), idnty(x){}//idnty constructor for adjacency list

	Vertex(Entity* ent,int x) : val(ent), idnty(x){}

	~Vertex(){
		delete val;
	}

	int getIdnty(){
		return idnty;
	}

};

class Graph{
	int totalVertices; //number of vertices, should be 100
	int keynum;  //square root of the vertices, will be used extensively for computations and whatnot
	vector<vector<Vertex*>> vertices;
	vector<Vertex*>::iterator iter;

	void addNeighbors(int);  //adds the nearby tiles to the designated tile's "neighbor list"

public:
	//initializes the graph, but does not connect any neighbors
	Graph(int numOfVertices):totalVertices(numOfVertices), keynum(sqrt(numOfVertices)){
		vertices.reserve(totalVertices);  //allocates space for the vector
		for (int i = 0; i < numOfVertices; i++){
			vector<Vertex*> temp;
			Vertex* v = new Vertex(i);

			temp.push_back(v);
			vertices.push_back(temp);
		}
	} 

	/*~Graph(){
		for (int i = 0; i < totalVertices; i++){
			iter = vertices.at(i).begin();
			while (iter != vertices.at(i).end()){
				delete *iter;
				++iter;
			}
			vertices.at(i).clear();
		}
	}*/

	void build(); /*utilizes addNeighnors to connect every tile in the graph 
	to its nearby neighbors  NOTE: I didn't include this in the constructor incase I wanted a blank graph*/
	
	void addEdge(int, Vertex*); //add some Vertex to tile(int)
	void removeEdge(int, Vertex*);  //delete some Vertex from tile(int)

	void BFS();  //breadth-first search, aka, most efficient path

	void printAdjList(); //prints adjacency list in console
	void printGrid();//prints out the graph in console, uses printGridSquare

	string printNeighbors(int);//prints out a tile's neighbors (decided against overloading <<, as that would been cancer)
	void test();  //testing function for testing some aspect of the program
};