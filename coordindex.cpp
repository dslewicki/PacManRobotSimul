#include "coordindex.h"

int coordToIndex(int x, int y, int keynum){
	return x*keynum + y;
}

int indexToRownum(int keynum, int z) {
	if (z - keynum < 0)
		return 0;

	return z/keynum;
}

int indexToColnum(int keynum, int z) {
	return z - ((z / keynum)*keynum);
}