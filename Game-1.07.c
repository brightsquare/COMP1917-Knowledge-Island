/*
 *  Game.c
 *	by Jabez Wilson, 5027406
 *	INCOMPLETE
 *	
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

#define NO_DISCIPLINE 6

#define NUM_RESOURCES 6
#define STARTING_POINTS_PER_PLAYER 2
#define NUM_VERTICES_PER_REGION 6
#define DIRECTIONS 4
#define REGIONS_PER_VERTEX 3

//I don't know how things turn out and this might be scraped
#define NUM_CENTRE 1
#define NUM_INNER (NUM_CENTRE*6)
 //the regions with two outside edges (not connected to anything else)
#define NUM_OUTER1 (NUM_CENTRE*6)
 //regions with only one not connected vertex
#define NUM_OUTER2 (NUM_CENTRE*6)

#define EVEN_ODD 1
#define ODD_EVEN 0

#define DEBUG_newGame 
#define DEBUG_printGrid 

//##########################################################################
//BEGINNING OF STRUCT DEFINITIONS
//##########################################################################
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

//##########################################################################
//BEGINNING OF STATIC FUNCTION DECLARATIONS
//##########################################################################

	static void printGrid(Game g);

//##########################################################################
//BEGINNING OF MAIN
//##########################################################################
	int main(int argc, char *argv[]){

		int a[] = {1,2,3};
		int b[] = {1,2,3};

		Game g = newGame(a,b);

		printGrid(g);
		disposeGame(g);
		return EXIT_SUCCESS;
	}

//##########################################################################
//BEGINNING OF FUNCTION DEFINITIONS
//##########################################################################

	Game newGame (int discipline[], int dice[]){
		Game ret = malloc(sizeof(struct _game));//freed

		vertex *tmp = NULL,*it = NULL;
		int i = 0,j=0;
		int centre = NUM_CENTRE,inner = NUM_INNER,out1 = NUM_OUTER1,out2 = NUM_OUTER2;
		assert(centre + inner + out1 + out2 == NUM_REGIONS);

		int linkType;
		
		/*
		<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		need to be altered later
		<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		*/

		ret->uniStart[0] = NULL;
		ret->uniStart[1] = NULL;
		ret->uniStart[2] = NULL;

		ret->numDice = 4;

		ret->dices = NULL;
		int numVertices = centre*6 + inner*3 + out1*2 + out1*3; 
		ret->origin = malloc(sizeof(vertex)*numVertices);//freed

		//following while sets all the values of Origin array to default
			//and creates a network with *next
			it = ret->origin;
			i = 0;
			while(i<numVertices){
				it->owner = NO_ONE;
		 		it->campus = VACANT_VERTEX;
		 		it->vertexID = i;
		 		it->ARC[0] = VACANT_ARC;
		 		it->ARC[1] = VACANT_ARC;
		 		it->ARC[2] = VACANT_ARC;
		 		it->ARC[3] = VACANT_ARC;

		 		it->neighbor[0] = NULL;
		 		it->neighbor[1] = NULL;
		 		it->neighbor[2] = NULL;
		 		it->neighbor[3] = NULL;
		 		if(i<numVertices-1){
		 			tmp = it;
		 			it++;
		 			tmp->next = it;
		 		}
		 		else{
		 			it->next = NULL;
		 		}
		 		i++;
			}
			tmp = ret->origin;

		//Initializing all links (neighbors)
			//set links between vertices 0-5 48-53;
			//RIGHT LEFT
			i = 0;
			while(i<3){
				tmp[2*i].neighbor[RIGHT] = &tmp[2*i+1];
				tmp[48+ 2*i].neighbor[RIGHT] = &tmp[48+ 2*i +1];
				tmp[2*i+1].neighbor[LEFT] = &tmp[2*i];
				tmp[48+ 2*i+1].neighbor[LEFT] = &tmp[48+ 2*i];
				i++;
			}

			i = 0;
			//UP DOWN
			while(i<2){
				tmp[i].neighbor[DOWN] = &tmp[i+3];
				tmp[i+3].neighbor[UP] = &tmp[i];
				
				tmp[49+ i].neighbor[DOWN] = &tmp[49+i+3];
				tmp[49+i+3].neighbor[UP] = &tmp[49+i];
				i++;
			}

			//sets links between 3rd - 2nd and 9th - 10th
			i = 0;
			while(i<4){
				tmp[2+i].neighbor[DOWN] = &tmp[7+i];
				tmp[7+i].neighbor[UP] = &tmp[2+i];

				tmp[43+i].neighbor[DOWN] = &tmp[48+i];
				tmp[48+i].neighbor[UP] = &tmp[43+i];
				i++;
			}

			//sets links within 3rd
			i = 0;
			while(i<3){
				tmp[6+ 2*i].neighbor[RIGHT] = &tmp[6 + 2*i +1];
				tmp[6+ 2*i +1].neighbor[LEFT] = &tmp[6 + 2*i];

				tmp[42+ 2*i].neighbor[RIGHT] = &tmp[42+ 2*i +1];
				tmp[42+ 2*i +1].neighbor[LEFT] = &tmp[42 + 2*i];
				i++;
			}

			//sets relation of 3rd and 9th with others
			i = 6;
			while(i<12){
				tmp[i].neighbor[DOWN] = &tmp[i+6];
				tmp[i+36].neighbor[UP] = &tmp[i+6+36];
				i++;
			}

			//sets links of all others only UP DOWN
			i = 12;
			while(i<42){
				tmp[i].neighbor[UP] = &tmp[i-6];
				tmp[i].neighbor[DOWN] = &tmp[i+6];
				i++;
			}

			i = 12;
			linkType = ODD_EVEN;
			while(i<42){
				if(linkType == ODD_EVEN){
					if(i%2!=0){
						tmp[i].neighbor[RIGHT] = &tmp[i+1];
						tmp[i+1].neighbor[LEFT] = &tmp[i];
					}
				}
				else {
					if(i%2==0){
						tmp[i].neighbor[RIGHT] = &tmp[i+1];
						tmp[i+1].neighbor[LEFT] = &tmp[i];
					}
				}
				i++;
				if(i%6==0){
					linkType = !linkType;
				}
			}
			assert(ret!=NULL);
			#ifdef DEBUG_newGame
				printf("ret!=NULL\n");
			#endif
		
		//Initializing all player values
			i = UNI_A;
			while(i<=UNI_C){
				g->playerObjects[i].playerID = i;
				g->playerObjects[i].KPI = 0;
				g->playerObjects[i].numARC = 0;

				g->playerObjects[i].numPatent = 0;
				g->playerObjects[i].numCampus = STARTING_POINTS_PER_PLAYER;
				g->playerObjects[i].numG08 = 0;
				g->playerObjects[i].numPublication = 0;
				for(j=0;j<NUM_RESOURCES;j++){
					g->playerObjects[i].ratio = 3;
				}

				g->playerObjects[i].resources[STUDENT_THD] = 0;
				g->playerObjects[i].resources[STUDENT_BPS] = 3;
				g->playerObjects[i].resources[STUDENT_BQN] = 3;
				g->playerObjects[i].resources[STUDENT_MJ] = 1;
				g->playerObjects[i].resources[STUDENT_MTV] = 1;
				g->playerObjects[i].resources[STUDENT_MMONEY]=1;
				i++;
			}
			//links still need to be made to vertices

		return ret;
	}

	void disposeGame (Game g){
		free(g->origin);
		free(g);
	}

	static void printGrid(Game g){
		assert(g != NULL);
		#ifdef DEBUG_printGrid
			printf("g!=NULL\n");
		#endif
		vertex *tmp;
		tmp = g->origin;
		assert(tmp !=  NULL);
		#ifdef DEBUG_printGrid
			printf("tmp!=NULL\n");
		#endif

		int i = 0;
		printf("    ID|    UP|  DOWN| RIGHT|  LEFT|  NEXT|\n");
		

		while(i<54){
			printf("%6d|",tmp->vertexID);
			if(tmp->neighbor[UP] != NULL)printf("%6d|",tmp->neighbor[UP]->vertexID);
			else printf("      |");
			if(tmp->neighbor[DOWN] != NULL)printf("%6d|",tmp->neighbor[DOWN]->vertexID);
			else printf("      |");
			if(tmp->neighbor[RIGHT] != NULL)printf("%6d|",tmp->neighbor[RIGHT]->vertexID);
			else printf("      |");
			if(tmp->neighbor[LEFT] != NULL)printf("%6d|",tmp->neighbor[LEFT]->vertexID);
			else printf("      |");
			if(tmp->next != NULL)printf("%6d|",tmp->next->vertexID);
			else printf("      |");
			printf("\n");
			i++;
			tmp++;

		}	
	}