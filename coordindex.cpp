#include "coordindex.h"

int coordToIndex(int x, int y, int keynum){
	return x*keynum + y;
}