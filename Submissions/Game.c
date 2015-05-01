/*
	Gamer struct submission by
	Jabez Wilson
	Paulus Sujono
	Sijia Chen
	Mattew Philips
*/
#include "Game-1.07.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define LAYERS 3

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3


	typedef struct _player{
		int playerID;
		int KPI;
		int numARC;
		int numPatent;
		int numCampus;
		int numG08;
		int numPublication;
		int resources[6],ratio[6];//<<<<<<ratio is important
		vertex *start[2];
	}player;

	typedef struct _vertex{
	 	//owner of this vertex or NULL
	 	player *owner;
	 	//campus at this vertex or VACANT_VERTEX
	 	int campus;
	 	//vertex Id of this vertex
	 	int vertexID;
	 	//ARC grants corresponding with neighbor, see example
	 	int ARC[4];
	  int region[3];
	 	//next pointers to neghboring vertices
	 	struct _vertex *next, *neighbor[4];
	 	//neighbor order is CLOCKWISE, example coming soon
	}vertex;
	/*
	Example for arc
	if arc grant  ARC_A is between two nodes say Ids 0 and 1
	then vertex 0 will have
	ARC[RIGHT] = ARC_A
	where neighbor[RIGHT] = {vertexID = 1}
	also for vertex 1
	ARC[LEFT] = ARC_A
	where neighbor[LEFT] = {vertexID = 0}
	*/
	typedef struct _region{
	 int regionID; 
	 int diceVal;
	 vertex* list[6];
	 int discipline;
	}region;

	//actual game
	struct _game{
	 vertex* origin;
	 region regions[NUM_REGIONS];
	 int whoseTurn;
	 int numDice;
	 int numG08;
	 int mostARC,mostPublication;
	 player playerObjects[NUM_UNIS];
	};