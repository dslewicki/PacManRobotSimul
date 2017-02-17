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

02/16/2017
So my roommate owes me and my other roommates >$1000, and we have video evidence of him agreeing to the bet with the terms clarified,
AND he was not under any duress, and he refuses to pay.  Oh yeah, there is a game over function when the pacbot is adjacent to the ghost.
Next step will be to get the ghost visible on the map no matter what, and then to automate movement.

02/12/2017
4:29 AM, realized I completely overlooked the fact that ghosts and dots can overlap, so I remedied that by adding another variable to hold
ghosts and all the stuff that comes with that.  I still need an internship and I have exams constantly.  If you are a recruiter for any company
that happens to be reading this, I swear I can be a lot more professional than this, and that I look great with your company logo.

02/09/2017
Finally, the mapping works. The robot can now see in all directions appropiately, AND its refresh occurs before the movement instead of after.
A fully comprehensive check has not been performed to confirm that the mapping is entirely bug-free, but now I can start working on the ghostses.

02/02/2017
I can detect walls from the north, but it does not draw it correctly.  I want to die.

01/26/2017
Worked on the way the PacBot would map out unknowns.  This has implementation has been coded in main.cpp for now, and will most
likely move to its respective class.  There are multiple issues with this push, as the robot can see around corners.  Additionally,
due to time constraints, main.cpp has been bombarded with a whole lot of code, specifically the controls and a bunch of other stuff.
I still need to automate the bot and add the ghosts.
 
01/03/2017
Nose is stuffy, but general movement for the robot is underway.  Next will be vision, where the map will be unknown at first, 
then as the bot turns each corner, everything it sees will be revealed.

As of 12/28/2016, a basic display representing the grid has been established, and the hierarchy of entities are being worked on.  
BFS has also been completed, and will be used in the algorithm which has yet to be realized.  A* algorithm may be used once the
robot fully maps out all tiles for better pathfinding.


As of 11/23/2016, the program is still in early shape, as no algorithm has been implemented as of yet, 
no display has been established, and the hierarchy of objects still hasn't been completed.  I also have to study for finals, so
that's definitely going to delay this.  