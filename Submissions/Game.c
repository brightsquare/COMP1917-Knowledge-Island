/*
	Gamer struct submission by
	Jabez Wilson
	Paulus Sujono
	Sijia Chen
	Mattew Philips
*/
#include "Game.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define LAYERS 3

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define NO_DISCIPLINE 6

#define NUM_RESOURCES 6
#define STARTING_POINTS_PER_PLAYER 2
#define NUM_VERTICES_PER_REGION 6
#define DIRECTIONS 4
#define REGIONS_PER_VERTEX 3


typedef struct _player{
	int playerID;
	int KPI;
	int numARC;
	int numPatent;
	int numCampus;
	int numG08;
	int numPublication;
	int resources[NUM_RESOURCES],ratio[NUM_RESOURCES];//<<<<<<ratio is important
	vertex *start[STARTING_POINTS_PER_PLAYER];
}player;

typedef struct _region{
 int regionID; 
 int diceVal;
 vertex* list[NUM_VERTICES_PER_REGION];
 int discipline;
}region;//actual game

typedef struct _vertex{
 	//owner of this vertex or NULL
 	player *owner;
 	//campus at this vertex or VACANT_VERTEX
 	int campus;
 	//vertex Id of this vertex
 	int vertexID;
 	//ARC grants corresponding with neighbor, see example
 	int ARC[DIRECTIONS];
    region *regions[REGIONS_PER_VERTEX];
 	//next pointers to neghboring vertices
 	struct _vertex *next, *neighbor[DIRECTIONS];
 	int training;
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


struct _game{
 vertex* origin;
 region regions[NUM_REGIONS];
 int whoseTurn;
 int diceValue;
 int numG08;
 player *mostARC,*mostPublication;
 player playerObjects[NUM_UNIS];
};