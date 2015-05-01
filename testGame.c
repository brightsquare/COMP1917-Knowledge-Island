#include "Game.h"

#include <stdio.h>
#include <assert.h>

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

static void testGame();

void main(int argc, char *argv[])
{
	testGame();
	return EXIT_SUCCESS;
}

static void testGame(){
  int i,j,k;

  //intiialize and check newGame
  int disciplines[] = DEFAULT_DISCIPLINES;
  int dice[] = DEFAULT_DICE;
	Game g = newGame(disciplines,dice);
	assert(g!=NULL);

	//############################
	//empty game or Terra Nullis
	//############################
		//getDiscipline get getDiceValue
		i = 0;
		while(i<NUM_REGIONS){
			assert(getDiscipline(g,i) == disciplines[i]);
			assert(getDiceValue(g,i) == dice[i]);
			i++;
		}

		assert(getMostARCs(g) == NO_ONE);
		assert(getMostPublications(g) == NO_ONE);
		assert(getTurnNumber(g) == -1);
		assert(getWhoseTurn(g) == NO_ONE);

		//player functions
		i = UNI_A
		while(i<=UNI_C){
			assert(getKPIpoints(g,i)==0);
			assert(getARCs(g,i)==0);
			assert(getG08s(g,i)==0);
			assert(getCampuses(g,i)==2);
			assert(getIPs(g,i)==0);
			assert(getPublications(g,i)==0);

			assert(getStudents(g,i,STUDENT_THD)==0);
			assert(getStudents(g,i,STUDENT_BPS)==3);
			assert(getStudents(g,i,STUDENT_BQN)==3);
			assert(getStudents(g,i,STUDENT_MJ)==1);
			assert(getStudents(g,i,STUDENT_MTV)==1);
			assert(getStudents(g,i,STUDENT_MMONEY)==1);
			
			j = 0;
			while(j<6){
				k=0;
				while(k<6){
					if(k!=j){
						assert(getExchangeRate(g,i,j,k)==3);
					}
				}
				j++;
			}
			i++;
		}



	disposeGame(g);
	printf("");
}