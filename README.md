# PacManRobotSimul
Simulated environment for the robot for the Pac-Man Robot competition.
This program will be used to test the algorithm for the competition, and will possibly be implemented into the robot itself.

A note about how the ghosts will be used to help us map the maze:


This is actually pretty straightforward, as we know the ghosts' locations at all times.
Because of this, we can see where they move.  This means that wherever the ghost moves,
there exists no wall, and hence, a valid path.  In terms of implementation for the simulation,
this will be achieved by 
1. Getting the tile index the ghost is at
2. Removing all other directional pointers besides the direction it came from(only after the start of the game)
3. and adding that tile object (not a reference/pointer) to the robot's internal map.
