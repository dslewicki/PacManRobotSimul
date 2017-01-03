#include "coordindex.h"

int coordToIndex(int r, int c, int keynum){
	if (r < 0 || c < 0 || r==keynum || c==keynum)
		return -1;
		
	return r*keynum + c;
}

int indexToRownum(int keynum, int z) {
	if (z - keynum < 0)
		return 0;

	return z/keynum;
}

int indexToColnum(int keynum, int z) {
	return z - ((z / keynum)*keynum);
}