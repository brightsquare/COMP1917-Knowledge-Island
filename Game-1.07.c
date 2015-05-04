/*
 *  Game.c
 *	by Jabez Wilson, 5027406
 *	INCOMPLETE
 *	log
 *	- newGame still incomplete
 *	- newGame creates a grid with all the neighbors and next
 *	- newGame initializes the regions
 *	- newGame initializes the regions and corresponding values in each vertex
 *	- goTo funstions fixed and ready to be used
 *	- oppsoiteDir function as well
 *
 *
 *
 *
 */

#include "Game-1.07.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define LAYERS 3

//the values for UP, DOWN,LEFT, RIGHT are defined anticlockwise
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

//I don't know how things turn out and this might be scraped
#define NUM_CENTRE 1
#define NUM_INNER (NUM_CENTRE*6)
 //the regions with two outside edges (not connected to anything else)
#define NUM_OUTER1 (NUM_CENTRE*6)
 //regions with only one not connected vertex
#define NUM_OUTER2 (NUM_CENTRE*6)

#define EVEN_ODD 1
#define ODD_EVEN 0

#define NUM_RESOURCES 6
#define STARTING_POINTS_PER_PLAYER 2
#define NUM_VERTICES_PER_REGION 6
#define DIRECTIONS 4
#define REGIONS_PER_VERTEX 3

#define DEBUG_newGame
#define DEBUG_region
//#define DEBUG_links

//#define DEBUG_printGrid
#define DEBUG_disposeGrid 
//#define DEBUG_oppositeDir
//#define DEBUG_goTo

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
				STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
				STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
				STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
				STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


//##########################################################################
//BEGINNING OF STRUCT DEFINITIONS
//##########################################################################
	typedef struct _vertex vertex;
	typedef struct _player player;
	typedef struct _region region;


	struct _vertex{
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
	};
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

	struct _player{
		int playerID;
		int KPI;
		int numARC;
		int numPatent;
		int numCampus;
		int numG08;
		int numPublication;
		int resources[NUM_RESOURCES],ratio[NUM_RESOURCES];//<<<<<<ratio is important
		vertex *start[STARTING_POINTS_PER_PLAYER];
	};

	struct _region{
	 int regionID; 
	 int requiredDiceVal;
	 vertex* surrounding[NUM_VERTICES_PER_REGION];
	 int discipline;
	};//actual game

	struct _game{
	 vertex* origin;
	 region* regions;
	 int whoseTurn;
	 int diceValue;
	 int numG08;
	 player *mostARC,*mostPublication;
	 player playerObjects[NUM_UNIS];
	};

//##########################################################################
//BEGINNING OF STATIC FUNCTION DECLARATIONS
//##########################################################################

	//prints the whole grid,
	//as a table having infoabout what each object in the grid points to
	static void printGrid(Game g);
	static void printRegionGrid(Game g);
	//returns pointer to vertex defined by path
	static vertex* goTo(vertex* origin,char * path,int* lastDir);
	//returns opposite direction
	//opppositeDir(UP) = DOWN
	static int oppositeDir(int i);
	//test functions
	static void testOppositeDir();
	static void testGoTo();

//##########################################################################
//BEGINNING OF MAIN
//##########################################################################
	int main(int argc, char *argv[]){

		int a[] = {1,2,3};
		int b[] = {1,2,3};

		Game g = newGame(a,b);
		
		#ifdef DEBUG_links
			printGrid(g);
		#endif

		#ifdef DEBUG_region
			printRegionGrid(g);
		#endif

		#ifdef DEBUG_goTo
			testGoTo();
			printf("GO TO PASSED\n");
		#endif
		#ifdef DEBUG_oppositeDir
			testOppositeDir();
			printf("OPPOSITE DIRECTION PASSED\n");
		#endif
		disposeGame(g);
		return EXIT_SUCCESS;
	}

//##########################################################################
//BEGINNING OF FUNCTION DEFINITIONS
//##########################################################################

	Game newGame (int discipline[], int dice[]){
		Game ret = malloc(sizeof(struct _game));//freed

		vertex *vertexTmp = NULL,*it = NULL;
		//region *regionTmp = NULL;
		int i = 0,j=0,k=0;
		int centre = NUM_CENTRE,inner = NUM_INNER,out1 = NUM_OUTER1,out2 = NUM_OUTER2;
		assert(centre + inner + out1 + out2 == NUM_REGIONS);
		int linkType;

		//intitilaizing the primary values
		//i.e the ones which need not be objects or pointers to objects
			ret->whoseTurn = NO_ONE;
			ret->diceValue = -1;
			ret->numG08 = 0;

			ret->mostARC = NULL;
			ret->mostPublication = NULL;

		int numVertices = centre*6 + inner*3 + out1*2 + out1*3;
		assert(numVertices == 54); 
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

				it->regions[0] = NULL;
				it->regions[0] = NULL;
				it->regions[0] = NULL;

				it->neighbor[0] = NULL;
				it->neighbor[1] = NULL;
				it->neighbor[2] = NULL;
				it->neighbor[3] = NULL;
				if(i<numVertices-1){
					vertexTmp = it;
					it++;
					vertexTmp->next = it;
				}
				else{
					it->next = NULL;
				}
				i++;
			}

		//Initializing all links (neighbors)
			vertexTmp = ret->origin;
			//set links between vertices 0-5 48-53;
			//RIGHT LEFT
			i = 0;
			while(i<3){
				vertexTmp[2*i].neighbor[RIGHT] = &vertexTmp[2*i+1];
				vertexTmp[48+ 2*i].neighbor[RIGHT] = &vertexTmp[48+ 2*i +1];
				vertexTmp[2*i+1].neighbor[LEFT] = &vertexTmp[2*i];
				vertexTmp[48+ 2*i+1].neighbor[LEFT] = &vertexTmp[48+ 2*i];
				i++;
			}

			i = 0;
			//UP DOWN
			while(i<2){
				vertexTmp[i].neighbor[DOWN] = &vertexTmp[i+3];
				vertexTmp[i+3].neighbor[UP] = &vertexTmp[i];
				
				vertexTmp[49+ i].neighbor[DOWN] = &vertexTmp[49+i+3];
				vertexTmp[49+i+3].neighbor[UP] = &vertexTmp[49+i];
				i++;
			}

			//sets links between 3rd - 2nd and 9th - 10th
			i = 0;
			while(i<4){
				vertexTmp[2+i].neighbor[DOWN] = &vertexTmp[7+i];
				vertexTmp[7+i].neighbor[UP] = &vertexTmp[2+i];

				vertexTmp[43+i].neighbor[DOWN] = &vertexTmp[48+i];
				vertexTmp[48+i].neighbor[UP] = &vertexTmp[43+i];
				i++;
			}

			//sets links within 3rd
			i = 0;
			while(i<3){
				vertexTmp[6+ 2*i].neighbor[RIGHT] = &vertexTmp[6 + 2*i +1];
				vertexTmp[6+ 2*i +1].neighbor[LEFT] = &vertexTmp[6 + 2*i];

				vertexTmp[42+ 2*i].neighbor[RIGHT] = &vertexTmp[42+ 2*i +1];
				vertexTmp[42+ 2*i +1].neighbor[LEFT] = &vertexTmp[42 + 2*i];
				i++;
			}

			//sets relation of 3rd and 9th with others
			i = 6;
			while(i<12){
				vertexTmp[i].neighbor[DOWN] = &vertexTmp[i+6];
				vertexTmp[i+36].neighbor[UP] = &vertexTmp[i-6+36];
				i++;
			}

			//sets links of all others only UP DOWN
			i = 12;
			while(i<42){
				vertexTmp[i].neighbor[UP] = &vertexTmp[i-6];
				vertexTmp[i].neighbor[DOWN] = &vertexTmp[i+6];
				i++;
			}

			i = 12;
			linkType = ODD_EVEN;
			while(i<42){
				if(linkType == ODD_EVEN){
					if(i%2!=0){
						vertexTmp[i].neighbor[RIGHT] = &vertexTmp[i+1];
						vertexTmp[i+1].neighbor[LEFT] = &vertexTmp[i];
					}
				}
				else {
					if(i%2==0){
						vertexTmp[i].neighbor[RIGHT] = &vertexTmp[i+1];
						vertexTmp[i+1].neighbor[LEFT] = &vertexTmp[i];
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

		ret->regions = malloc(sizeof(region)*NUM_REGIONS);
		//intiitalizing regions
			int startRegion[NUM_REGIONS]={
				6,18,30,2,13,25,37,0,8,20,32,44,4,15,27,39,10,22,34
			};
			i = 0;
			while(i<NUM_REGIONS){
				#ifdef DEBUG_region
					printf("%d\n",i);
				#endif


				ret->regions[i].regionID = i;
				ret->regions[i].requiredDiceVal = dice[i];
				ret->regions[i].discipline = discipline[i];

				it = &(ret->origin[startRegion[i]]);
				j=0;
				ret->regions[i].surrounding[j] = it;
				it = it->neighbor[RIGHT];j++;
				ret->regions[i].surrounding[j] = it;
				it = it->neighbor[DOWN];j++;
				ret->regions[i].surrounding[j] = it;
				it = it->neighbor[DOWN];j++;
				ret->regions[i].surrounding[j] = it;
				it = it->neighbor[LEFT];j++;
				ret->regions[i].surrounding[j] = it;
				it = it->neighbor[UP];j++;
				ret->regions[i].surrounding[j] = it;
				
				//relation from vertex to the appropriate region
				j=0;
				while(j<NUM_VERTICES_PER_REGION){
					it = ret->regions[i].surrounding[j];
					k=0;
					while(it->regions[k] != NULL && k< REGIONS_PER_VERTEX){
						k++;
					}
					if(k==REGIONS_PER_VERTEX){
						printf("vertex id %d \nregion id %d \nregion id %d \nregion id %d",it->vertexID,it->regions[0]->regionID,it->regions[1]->regionID,it->regions[2]->regionID);
					}
					assert(k!=REGIONS_PER_VERTEX);
					it->regions[k] = &(ret->regions[i]);
					j++;
				}
				
				i++;
			}

		return ret;
	}

	void disposeGame (Game g){
		free(g->origin);
		free(g->regions);
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

	static vertex* goTo(vertex* origin,char* path,int* lastDir){
		vertex* traveller;
		char* pathDir = path;
		assert(*pathDir == 'R' || *pathDir == 'L' ||*pathDir == 'B' );
		int right = FALSE,left = FALSE,it = 0,last;
		int tmp;

		traveller = origin;

		//the first 'shift' is done at origin, 
		//this is straightforward as the relative right 'R' is the left neighbor when you look form above
		if(*pathDir == 'R'){
			//the direction of neighbor is opp of the pathDir
			traveller = traveller->neighbor[DOWN];
			last = DOWN;
		}
		else {
			traveller = traveller->neighbor[RIGHT];
			last = RIGHT;	
		}
		pathDir++;

		//after the first shift it has to enter a while to 
		//get through the remaining path 
		while(*pathDir!='\0'){
			//it is iterator and it will start from the opposite of last
			//as last was relative to the previous vertex 
			it = oppositeDir(last);
			left = FALSE;right = FALSE;
			while(!((left == TRUE && *pathDir == 'L')||(right == TRUE && *pathDir == 'R'))){
				it++;
				if(it==4){
					it=0;
				}
				if(it == oppositeDir(last)){
					left = TRUE;
					right = TRUE;
				}
				else if(traveller->neighbor[it]!=NULL){
					if(right == FALSE){
						right = TRUE;
					}
					else if(left == FALSE){
						left = TRUE;
					}
					tmp = it;
				}

			}
			traveller = traveller->neighbor[tmp];
			last = tmp;
			pathDir++;
		}

		if(lastDir != NULL){
			*lastDir = last;
		}

		return traveller;
	}
	static int oppositeDir(int i){
		assert(i>=0&&i<4);
		int ret;
		ret = i+2;
		if(ret>=4){
			ret-=4;
		}

		return ret;
	}

	static void printRegionGrid(Game g){
		printf("    ID|V1    |V2    |V3    |V4    |V5    |V6    |\n");
		region *regionTmp = g->regions;
		vertex *vertexTmp = g->origin;
		int i =0,j;
		while(i<NUM_REGIONS){
			printf("%6d|",regionTmp->regionID);
			j=0;
			while(j<6){
				printf("%6d|",regionTmp->surrounding[j]->vertexID);
				j++;
			}
			printf("\n");
			regionTmp++;
			i++;
		}
		printf("\n\n");
		printf("    ID|     1|     2|     3|\n");
		
		i=0;
		while(i<54){
			printf("%6d|",vertexTmp->vertexID);
			j =0;
			while(j<3){
				if(vertexTmp->regions[j]!=NULL)
					printf("%6d|",vertexTmp->regions[j]->regionID);
				else
					printf("      ");
				j++;
			}
			i++;
			vertexTmp++;
			printf("\n");
		}
	}

//##########################################################################
//TESTS
//##########################################################################
	static void testOppositeDir(){
		assert(oppositeDir(UP)==DOWN);
		assert(oppositeDir(DOWN)==UP);
		assert(oppositeDir(LEFT)==RIGHT);
		assert(oppositeDir(RIGHT)==LEFT);
	}

	static void testGoTo(){

		int something;
  		int disciplines[] = DEFAULT_DISCIPLINES;
  		int dice[] = DEFAULT_DICE;
		Game g = newGame(disciplines,dice);
		assert(goTo(g->origin,"RRR",NULL)->vertexID == 7);
		assert(goTo(g->origin,"LLL",NULL)->vertexID == 5);
		assert(goTo(g->origin,"RLR",NULL)->vertexID == 14);
		assert(goTo(g->origin,"LRL",NULL)->vertexID == 5);

		assert(goTo(g->origin,"L",NULL)->vertexID == 1);
		assert(goTo(g->origin,"R",NULL)->vertexID == 3);
		disposeGame(g);
	}