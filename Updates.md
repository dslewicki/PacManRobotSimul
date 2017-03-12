02/23/2017
"Please make the exams stop, please."-me
1. Fixed a bug where after pressing a key for the pacbot manual movement, it waited for a second and then moved.
This was due _getch() returning a prefix of 224, and if you called it again, it would return the whole thing.  Like what.
2. Made the ghost visible on the memory map by literally just adding it to the map.
3. Starting work on automated movement for the ghosts


02/18/2017
THON has started and I'm busy doing infinite amounts of work, like adding a buglist and moving some chunks of code like
making a new look() function from the code in main.cpp to the Map.cpp.
03/11/2017
-actually decided to use basic oop to streamline code
-starting work on multiple ghost movement
-need to plan out individual ghost personalities

03/10/2017
-made functions validconnections(), move(), and advance()
-corrected(?) general movement for ghost, need more testing to verify
-some other stuff

03/09/2017
-Made a function isWall() that determines whether or not there is a wall between two tiles, and returns other connections if there is a wall
-Made some progress on the general ghost movement
-i want to die

03/07/2017
had to get some hw done before working on this, anyhway

-Made an update and bugs file for convenience
-Ghost is now visible on map at all times
-Starting automated movement
-im too tired to remember the rest, but stuff changed

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