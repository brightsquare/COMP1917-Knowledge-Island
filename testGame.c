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

int main(int argc, char *argv[])
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
    
    throwDice(g,6);
    action a1;
    a1.actionCode=OBTAIN_ARC;
    a1.destination[0]="L";
    a1.destination[1]="\0";
    makeAction(g,a1);
    //check isLegal(not finished)
    
    assert(getMostARCs(g) == UNI_A);
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_A);
    
    assert(getKPIpoints(g,UNI_A)==12); //Having the most ARC grants so get 10 KPIs
    assert(getARCs(g,UNI_A)==1);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==2);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==0);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==2);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==2);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==2);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==1);
    
    i=UNI_B;
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

    action a2;
    a2.actionCode=OBTAIN_ARC;
    a2.destination[0]="L";
    a2.destination[1]="R";
    a2.destination[2]="\0";
    makeAction(g,a2);
    
    //check isLegal(not finished)
    
    assert(getMostARCs(g) == UNI_A);
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_A);
    
    assert(getKPIpoints(g,UNI_A)==14);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==2);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==0);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==1);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==1);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==2);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==1);
    
    i=UNI_B;
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

    action a3;
    a3.actionCode=BUILD_CAMPUS;
    a3.destination[0]="L";
    a3.destination[1]="R";
    a3.destination[2]="\0";
    makeAction(g,a3);
    
    //check isLegal(not finished)
    
    assert(getMostARCs(g) == UNI_A);
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_A);
    
    assert(getKPIpoints(g,UNI_A)==24);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==3);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==0);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==0);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==1);
    
    i=UNI_B;
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

    throwDice(g,9);
    action a1;
    a1.actionCode=OBTAIN_ARC;
    a1.destination[0]="L";
    a1.destination[1]="\0";
    makeAction(g,a1);
    
    assert(getMostARCs(g) == UNI_A);
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_B);
    
    assert(getKPIpoints(g,UNI_B)==2);
    assert(getARCs(g,UNI_B)==1);
    assert(getG08s(g,UNI_B)==0);
    assert(getCampuses(g,UNI_B)==2);
    assert(getIPs(g,UNI_B)==0);
    assert(getPublications(g,UNI_B)==0);
    
    assert(getStudents(g,UNI_B,STUDENT_THD)==0);
    assert(getStudents(g,UNI_B,STUDENT_BPS)==2);
    assert(getStudents(g,UNI_B,STUDENT_BQN)==3);
    assert(getStudents(g,UNI_B,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_B,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_B,STUDENT_MMONEY)==1);
    
    //check UNI_A is not change
    assert(getKPIpoints(g,UNI_A)==24);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==3);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==0);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==0);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==1);
    
    //check UNI_C is not change
    assert(getKPIpoints(g,UNI_C)==0);
    assert(getARCs(g,UNI_C)==0);
    assert(getG08s(g,UNI_C)==0);
    assert(getCampuses(g,UNI_C)==2);
    assert(getIPs(g,UNI_C)==0);
    assert(getPublications(g,UNI_C)==0);
    
    assert(getStudents(g,UNI_C,STUDENT_THD)==0);
    assert(getStudents(g,UNI_C,STUDENT_BPS)==3);
    assert(getStudents(g,UNI_C,STUDENT_BQN)==3);
    assert(getStudents(g,UNI_C,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_C,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_C,STUDENT_MMONEY)==1);
    
    action a2;
    a2.actionCode=OBTAIN_ARC;
    a2.destination[0]="L";
    a2.destination[1]="R";
    a2.destination[2]="\0";
    makeAction(g,a2);
    
    assert(getMostARCs(g) == NO_ONE); //both UNI_A and UNI_B have 2 ARCs
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_B);
    
    assert(getKPIpoints(g,UNI_B)==4);
    assert(getARCs(g,UNI_B)==2);
    assert(getG08s(g,UNI_B)==0);
    assert(getCampuses(g,UNI_B)==2);
    assert(getIPs(g,UNI_B)==0);
    assert(getPublications(g,UNI_B)==0);
    
    assert(getStudents(g,UNI_B,STUDENT_THD)==0);
    assert(getStudents(g,UNI_B,STUDENT_BPS)==1);
    assert(getStudents(g,UNI_B,STUDENT_BQN)==2);
    assert(getStudents(g,UNI_B,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_B,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_B,STUDENT_MMONEY)==1);
    
    //check UNI_A is not change
    assert(getKPIpoints(g,UNI_A)==24);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==3);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==0);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==0);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==1);
    
    //check UNI_C is not change
    assert(getKPIpoints(g,UNI_C)==0);
    assert(getARCs(g,UNI_C)==0);
    assert(getG08s(g,UNI_C)==0);
    assert(getCampuses(g,UNI_C)==2);
    assert(getIPs(g,UNI_C)==0);
    assert(getPublications(g,UNI_C)==0);
    
    assert(getStudents(g,UNI_C,STUDENT_THD)==0);
    assert(getStudents(g,UNI_C,STUDENT_BPS)==3);
    assert(getStudents(g,UNI_C,STUDENT_BQN)==3);
    assert(getStudents(g,UNI_C,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_C,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_C,STUDENT_MMONEY)==1);

    action a3;
    a3.actionCode=BUILD_CAMPUS;
    a3.destination[0]="L";
    a3.destination[1]="R";
    a3.destination[2]="\0";
    makeAction(g,a3);
    
    assert(getMostARCs(g) == NO_ONE); //both UNI_A and UNI_B have 2 ARCs
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_B);
    
    assert(getKPIpoints(g,UNI_B)==14);
    assert(getARCs(g,UNI_B)==2);
    assert(getG08s(g,UNI_B)==0);
    assert(getCampuses(g,UNI_B)==3);
    assert(getIPs(g,UNI_B)==0);
    assert(getPublications(g,UNI_B)==0);
    
    assert(getStudents(g,UNI_B,STUDENT_THD)==0);
    assert(getStudents(g,UNI_B,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_B,STUDENT_BQN)==1);
    assert(getStudents(g,UNI_B,STUDENT_MJ)==0);
    assert(getStudents(g,UNI_B,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_B,STUDENT_MMONEY)==1);
    
    //check UNI_A is not change
    assert(getKPIpoints(g,UNI_A)==24);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==3);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==0);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==0);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==1);
    
    //check UNI_C is not change
    assert(getKPIpoints(g,UNI_C)==0);
    assert(getARCs(g,UNI_C)==0);
    assert(getG08s(g,UNI_C)==0);
    assert(getCampuses(g,UNI_C)==2);
    assert(getIPs(g,UNI_C)==0);
    assert(getPublications(g,UNI_C)==0);
    
    assert(getStudents(g,UNI_C,STUDENT_THD)==0);
    assert(getStudents(g,UNI_C,STUDENT_BPS)==3);
    assert(getStudents(g,UNI_C,STUDENT_BQN)==3);
    assert(getStudents(g,UNI_C,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_C,STUDENT_MTV)==1);
    assert(getStudents(g,UNI_C,STUDENT_MMONEY)==1);

    throwDice(g,7);
    action a1;
    a1.actionCode=OBTAIN_ARC;
    a1.destination[0]="L";
    a1.destination[1]="\0";
    makeAction(g,a1);
    
    assert(getMostARCs(g) == NO_ONE); //both UNI_A and UNI_B have 2 ARCs
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_B);
    
    assert(getKPIpoints(g,UNI_C)==2);
    assert(getARCs(g,UNI_C)==1);
    assert(getG08s(g,UNI_C)==0);
    assert(getCampuses(g,UNI_C)==2);
    assert(getIPs(g,UNI_C)==0);
    assert(getPublications(g,UNI_C)==0);
    
    assert(getStudents(g,UNI_C,STUDENT_THD)==2);
    assert(getStudents(g,UNI_C,STUDENT_BPS)==2);
    assert(getStudents(g,UNI_C,STUDENT_BQN)==2);
    assert(getStudents(g,UNI_C,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_C,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_C,STUDENT_MMONEY)==0);
    
    //check UNI_A all MTV and M$ students decide to switch to ThD's
    assert(getKPIpoints(g,UNI_A)==24);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==3);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==1);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==0);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==0);

    //check UNI_B all MTV and M$ students decide to switch to ThD's
    assert(getKPIpoints(g,UNI_B)==14);
    assert(getARCs(g,UNI_B)==2);
    assert(getG08s(g,UNI_B)==0);
    assert(getCampuses(g,UNI_B)==3);
    assert(getIPs(g,UNI_B)==0);
    assert(getPublications(g,UNI_B)==0);
    
    assert(getStudents(g,UNI_B,STUDENT_THD)==1);
    assert(getStudents(g,UNI_B,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_B,STUDENT_BQN)==1);
    assert(getStudents(g,UNI_B,STUDENT_MJ)==0);
    assert(getStudents(g,UNI_B,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_B,STUDENT_MMONEY)==0);

    a2.actionCode=OBTAIN_ARC;
    a2.destination[0]="L";
    a2.destination[1]="R";
    a2.destination[2]="\0";
    makeAction(g,a2);
    
    assert(getMostARCs(g) == NO_ONE); //all UNIs have 2 ARCs
    assert(getMostPublications(g) == NO_ONE);
    assert(getTurnNumber(g) == 0);
    assert(getWhoseTurn(g) == UNI_B);
    
    assert(getKPIpoints(g,UNI_C)==4);
    assert(getARCs(g,UNI_C)==2);
    assert(getG08s(g,UNI_C)==0);
    assert(getCampuses(g,UNI_C)==2);
    assert(getIPs(g,UNI_C)==0);
    assert(getPublications(g,UNI_C)==0);
    
    assert(getStudents(g,UNI_C,STUDENT_THD)==2);
    assert(getStudents(g,UNI_C,STUDENT_BPS)==1);
    assert(getStudents(g,UNI_C,STUDENT_BQN)==1);
    assert(getStudents(g,UNI_C,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_C,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_C,STUDENT_MMONEY)==0);
    
    //check UNI_A is no change
    assert(getKPIpoints(g,UNI_A)==24);
    assert(getARCs(g,UNI_A)==2);
    assert(getG08s(g,UNI_A)==0);
    assert(getCampuses(g,UNI_A)==3);
    assert(getIPs(g,UNI_A)==0);
    assert(getPublications(g,UNI_A)==0);
    
    
    assert(getStudents(g,UNI_A,STUDENT_THD)==1);
    assert(getStudents(g,UNI_A,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_A,STUDENT_BQN)==0);
    assert(getStudents(g,UNI_A,STUDENT_MJ)==1);
    assert(getStudents(g,UNI_A,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY)==0);
    
    //check UNI_B is no change
    assert(getKPIpoints(g,UNI_B)==14);
    assert(getARCs(g,UNI_B)==2);
    assert(getG08s(g,UNI_B)==0);
    assert(getCampuses(g,UNI_B)==3);
    assert(getIPs(g,UNI_B)==0);
    assert(getPublications(g,UNI_B)==0);
    
    assert(getStudents(g,UNI_B,STUDENT_THD)==1);
    assert(getStudents(g,UNI_B,STUDENT_BPS)==0);
    assert(getStudents(g,UNI_B,STUDENT_BQN)==1);
    assert(getStudents(g,UNI_B,STUDENT_MJ)==0);
    assert(getStudents(g,UNI_B,STUDENT_MTV)==0);
    assert(getStudents(g,UNI_B,STUDENT_MMONEY)==0);
    
    //turn 0 is finished

    

    /*
     * disposeGame to getMostArcs           Paulus
     * getMostPublications to getKPIpoints  Matt
     * getArcs to end                       Sijia
     */

	disposeGame(g);
	printf("");
}





     
    

