# PacManRobotSimul
Simulated environment for the robot for the Pac-Man Robot competition.
This program will be used to test the algorithm for the competition, and will possibly be implemented into the robot itself.

#SUPER BRIEF SUMMARY OF THE CODE
-So here's how everything works in a nutshell.
Within the Graph.cpp, there are two classes; Tile and Map.
The Tile class has the following private members.

--
class Tile{
Entity *val;
	Ghost *ghost;  //reference to a "Ghost" object (will be explained later)
	int indexVal;  //integer that represents the Entity's location within the maze, ranges from 0 to (n-1), where n in this case is 100 tiles, because 10x10.
	Tile* north;  //these are references to the tiles adjacent to this current one, and are marked as null if there is a wall.
	Tile* south;
	Tile* west;
	Tile* east;
	vector<Tile*> neighbors;  //dynamic container that holds all adjacent non-wall tiles.
	vector<Tile*>::iterator iter;  //used to navigate thru the vector
--

The Map class is basically a bunch of tiles that form a maze.


##Explanations of each class

###Graph.h

####The Tile class
-



A note about how the ghosts will be used to help us map the maze:

This is actually pretty straightforward, as we know the ghosts' locations at all times.
Because of this, we can see where they move.  This means that wherever the ghost moves,
there exists no wall, and hence, a valid path.  In terms of implementation for the simulation,
this will be achieved by 
1. Getting the tile index the ghost is at
2. Removing all other directional pointers besides the direction it came from(only after the start of the game)
3. and adding that tile object (not a reference/pointer) to the robot's internal map.

References: 
http://gameinternals.com/post/2072558330/understanding-pac-man-ghost-behavior
