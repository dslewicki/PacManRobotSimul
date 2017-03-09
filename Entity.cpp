#include "Entities.h"


char Roamer::rand_dir() {
	int rando;
	int prev;

		//choose a random direction besides the one you were traveling with
		if (getprev_dir() == 'n')
			prev = 0;
		if (getprev_dir() == 'e')
			prev = 1;
		if (getprev_dir() == 's')
			prev = 2;
		if (getprev_dir() == 'w')
			prev = 3;

		rando = rand() % 4;
		//if it its the same direction, change it
		if (rando == prev) 
			prev = 3 - prev;
		
		switch (prev) {
		case 0:
			setprev_dir('n');
			return 'n';
			break;
		case 1:
			setprev_dir('e');
			return 'e';
			break;
		case 2:
			setprev_dir('s');
			return 's';
			break;
		case 3:
			setprev_dir('w');
			return 'w';
			break;
		}
		
}

void Ghost::move_scatter(int cornerpos) {
	;
}

void Ghost::move_chase(int pacpos) {
	;
}

//void Roamer::move() {	;}

int Ghost::move(int currentpos, int targetpos, bool intersects[22]){//generic movement pattern, direction priority is up>left>down when heading towards target
	int endtile=0;
	char move_dir=0;
	if (intersects[currentpos])
		move_dir = rand_dir();
	
	//keep walking in previous direction


	return endtile;
}

