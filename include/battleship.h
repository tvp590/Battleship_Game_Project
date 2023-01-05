#include "stdbool.h"

struct Location {
	int c;
	int r;
};

struct Vessel {
	char name[20];
	bool sunk;
	unsigned int length;
	unsigned int hits;
	struct Location vesselLocations[5];
	struct Location alreadyHit[5];
};

