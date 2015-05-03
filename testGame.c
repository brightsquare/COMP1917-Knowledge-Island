#include "Game.h"

#include <stdio.h>
#include <assert.h>

#define BOARD_REGIONS 19
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
				STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
				STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
				STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
				STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
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
		assert()

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
	assert(isLegalAction(g,a1)==TRUE);
	makeAction(g,a1);
	
	//check isLegal(not finished)
	
	assert(getMostARCs(g) == NO_ONE);
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
	disposeGame(g);


	//########################################
	// Paulus' test functions
	//########################################

	/*
	 * test for:
	 * void disposeGame (Game g);
	 */

	// N/A
	
	/*
	 * test for:
	 * void makeAction (Game g, action a);
	 */

	// N/A

	/*
	 * test for:
	 * void throwDice (Game g, int diceScore);
	 */

	// N/A
	
	/*
	 * test for:
	 *int getDiscipline (Game g, int regionID);
	 */

	Game gameForGetDisciplineTest;

	// All THD disciplines
	int disciplinesTHD[] = {
		STUDENT_THD, STUDENT_THD, STUDENT_THD, STUDENT_THD,
		STUDENT_THD, STUDENT_THD, STUDENT_THD, STUDENT_THD,
		STUDENT_THD, STUDENT_THD, STUDENT_THD, STUDENT_THD,
		STUDENT_THD, STUDENT_THD, STUDENT_THD, STUDENT_THD,
		STUDENT_THD, STUDENT_THD, STUDENT_THD
	};

	// All BPS disciplines
	int disciplinesBPS[] = {
		STUDENT_BPS, STUDENT_BPS, STUDENT_BPS, STUDENT_BPS,
		STUDENT_BPS, STUDENT_BPS, STUDENT_BPS, STUDENT_BPS,
		STUDENT_BPS, STUDENT_BPS, STUDENT_BPS, STUDENT_BPS,
		STUDENT_BPS, STUDENT_BPS, STUDENT_BPS, STUDENT_BPS,
		STUDENT_BPS, STUDENT_BPS, STUDENT_BPS
	};

	// All BQN disciplines
	int disciplinesBQN[] = {
		STUDENT_BQN, STUDENT_BQN, STUDENT_BQN, STUDENT_BQN,
		STUDENT_BQN, STUDENT_BQN, STUDENT_BQN, STUDENT_BQN,
		STUDENT_BQN, STUDENT_BQN, STUDENT_BQN, STUDENT_BQN,
		STUDENT_BQN, STUDENT_BQN, STUDENT_BQN, STUDENT_BQN,
		STUDENT_BQN, STUDENT_BQN, STUDENT_BQN
	};

	// All MJ disciplines
	int disciplinesMJ[] = {
		STUDENT_MJ, STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
		STUDENT_MJ, STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
		STUDENT_MJ, STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
		STUDENT_MJ, STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
		STUDENT_MJ, STUDENT_MJ, STUDENT_MJ
	};

	// All MMONEY disciplines
	int disciplinesMMONEY[] = {
		STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY,
		STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY,
		STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY,
		STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY,
		STUDENT_MMONEY, STUDENT_MMONEY, STUDENT_MMONEY
	};

	// All MTV disciplines
	int disciplinesMTV[] = {
		STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV,
		STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV,
		STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV,
		STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV,
		STUDENT_MTV, STUDENT_MTV, STUDENT_MTV
	};

	// Custom disciplines
	int disciplinesCustom[] = {
		STUDENT_MTV, STUDENT_THD, STUDENT_MJ, STUDENT_MMONEY,
		STUDENT_BPS, STUDENT_BPS, STUDENT_BQN, STUDENT_MJ,
		STUDENT_THD, STUDENT_MTV, STUDENT_THD, STUDENT_MMONEY,
		STUDENT_BQN, STUDENT_BQN, STUDENT_MJ, STUDENT_MTV,
		STUDENT_BPS, STUDENT_THD, STUDENT_THD
	};




	gameForGetDisciplineTest = newGame(DEFAULT_DISCIPLINES, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplines[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesTHD, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesTHD[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesBPS, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesBPS[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesBQN, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesBQN[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesMJ, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesMJ[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesMMONEY, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesMMONEY[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesMTV, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesMTV[counterForGetDisciplineTest]);
	}

	gameForGetDisciplineTest = newGame(disciplinesCustom, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiscipline(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			disciplinesCustom[counterForGetDisciplineTest]);
	}
	
	/*
	 * test for:
	 * int getDiceValue (Game g, int regionID);
	 */

	Game gameForGetDiceValue;

	int diceCustom1[] = {
		3, 1, 4, 1,
		5, 9, 2, 6,
		5, 3, 5, 8,
		9, 7, 9, 3,
		2, 3, 8
	};

	int diceCustom2[] = {
		6, 2, 6, 4,
		3, 3, 8, 3,
		2, 7, 9, 5,
		0, 2, 8, 8,
		4, 1, 9
	};

	int diceCustom3[] = {
		10, 11, 12, 0,
		10, 11, 12, 0,
		10, 11, 12, 0,
		10, 11, 12, 0,
		11, 12, 0
	};

	gameForGetDiceValue = newGame(DEFAULT_DISCIPLINES, dice);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiceValue(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			dice[counterForGetDisciplineTest]);
	}

	gameForGetDiceValue = newGame(DEFAULT_DISCIPLINES, diceCustom1);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiceValue(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			diceCustom1[counterForGetDisciplineTest]);
	}

	gameForGetDiceValue = newGame(DEFAULT_DISCIPLINES, diceCustom2);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiceValue(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			diceCustom2[counterForGetDisciplineTest]);
	}

	gameForGetDiceValue = newGame(DEFAULT_DISCIPLINES, diceCustom3);

	// Check all regions in the board
	int counterForGetDisciplineTest = 0;
	while (counterForGetDisciplineTest < BOARD_REGIONS) {
		assert(getDiceValue(gameForGetDisciplineTest,
			counterForGetDisciplineTest),
			diceCustom3[counterForGetDisciplineTest]);
	}
	
	/*
	 * test for:
	 * int getMostARCs (Game g);
	 */


	// Not finished yet...

	// Simulates an 11 roll game, dice rolls: 2...11
	Game gameForGetDisciplineTest = newGame(disciplines, dice);
	assert(gameForGetDisciplineTest != NULL);
	int diceScore = 2;
	int turnNumber = 0;
	int whoseTurn = UNI_A;
	i = UNI_A;

	while (diceScore <= 12) {
		throwDice (g, diceScore);

		//cycles through the players each time turnNumber is a multiple of 3
		whoseTurn = (turnNumber%NUM_UNIS)+1;
		//test the easy getter functions
		assert(getWhoseTurn(g) == whoseTurn);
		assert(getTurnNumber(g) == turnNumber);
		//nobody has made any actions
		while(i<=UNI_C){
			assert(getKPIpoints(g,i)==0);
			i++;
		}
		assert(getMostPublications(g) == NO_ONE);



		diceScore++;
		turnNumber++;
	}

	//########################################
	// End Paulus' test functions
	//########################################


	//####################
	//Matt's test functions
	//####################

	Game g = newGame(disciplines,dice);
	assert(g!=NULL);
	//Changes the game state 11 times
	//DiceScore thrown 2,3,4...,12
	int diceScore = 2;
	int turnNumber = 0;
	int whoseTurn = UNI_A;
	i = UNI_A;
		
	
	while (diceScore <= 12) {
		throwDice (g, diceScore);

		//cycles through the players each time turnNumber is a multiple of 3
		whoseTurn = (turnNumber%NUM_UNIS)+1;
		//test the easy getter functions
		assert(getWhoseTurn(g) == whoseTurn);
		assert(getTurnNumber(g) == turnNumber);
		//nobody has made any actions
		while(i<=UNI_C){
			assert(getKPIpoints(g,i)==0);
			i++;
		}
		assert(getMostPublications(g) == NO_ONE);



		diceScore++;
		turnNumber++;
	}

	printf("Matt's getter functions passed after game state change!\n");

	//Test the getCampus and getARC

	path pathToVertex[0] = '\0';

	assert(getCampus(g, pathToVertex) == CAMPUS_A);

	//Path to the vertex is an array with L for Left, R for Right and B for back.
	//How are we going to represent that? 
	//Not sure whether the 0 at the end is meant to be a 0 or a \0 
	pathToVertex[] = {'R','\0'};

	assert(getCampus(g, pathToVertex) == VACANT_VERTEX);
	assert(getARC(g,pathToVertex) == VACANT_ARC);

	pathToVertex[] = {'R','R','R','R','R','\0'};

	assert(getCampus(g, pathToVertex) == CAMPUS_B);
	assert(getARC(g, pathToVertex) == VACANT_ARC);

	pathToVertex[] = {'R','B','\0'};
	assert(getCampus(g, pathToVertex) == CAMPUS_A);
	assert(getARC(g, pathToVertex) == VACANT_ARC);


	printf("Matt's getCampus and getArc functions passed!\n");

	action exampleActionMatt;
	exampleActionMatt.actionCode = OBTAIN_ARC; 
	exampleActionMatt.destination[0] = 'R';
	exampleActionMatt.destination[1] = '\0';
	exampleActionMatt.disciplineFrom = 6;
	exampleActionMatt.disciplineTo = 6;
	
	diceScore = 2;
	while (whoseTurn(g) <= UNI_C){

		

		
		if(whoseTurn(g)==UNI_A){
			
			assert (getCampus(g, exampleActionMatt.destination) == CAMPUS_A);
			assert (getARC(g, exampleActionMatt.destination) == VACANT_ARC);

			assert(isLegalAction(g,exampleActionMatt) == TRUE);
			makeAction(g,exampleActionMatt);

			assert(getKPIpoints(g, UNI_A) == 2);
			assert(getKPIpoints(g, UNI_B) == 0);
			assert(getKPIpoints(g, UNI_C) == 0);

			assert(getStudents(g, UNI_A, STUDENT_BPS) == 2);
			assert(getStudents(g, UNI_A, STUDENT_BQN) == 2);

			assert (getARC(g, exampleActionMatt.destination) == ARC_A);
	
		}else if (whoseTurn(g)==UNI_B){
			exampleActionMatt.destination[] = {'L','L','L','L','L','\0'};
			
			assert (getCampus(g, exampleActionMatt.destination) == CAMPUS_B);
			assert (getARC(g, exampleActionMatt.destination) == VACANT_ARC);
			
			assert(isLegalAction(g,exampleActionMatt) == TRUE);
			makeAction(g,exampleActionMatt);

			assert(getKPIpoints(g, UNI_A) == 2);
			assert(getKPIpoints(g, UNI_B) == 2);
			assert(getKPIpoints(g, UNI_C) == 0);
			assert(getStudents(g, UNI_B, STUDENT_BPS) == 2);
			assert(getStudents(g, UNI_B, STUDENT_BQN) == 2);

			assert (getARC(g, exampleActionMatt.destination) == ARC_B);

		}else {
			exampleActionMatt.destination[] = {'R','R','R','R','R','\0'};
			
			assert (getCampus(g, exampleActionMatt.destination) == CAMPUS_A);
			assert (getARC(g, exampleActionMatt.destination) == VACANT_ARC);

			assert(isLegalAction(g,exampleActionMatt) == TRUE);
			makeAction(g,exampleActionMatt);

			assert(getKPIpoints(g, UNI_A) == 2);
			assert(getKPIpoints(g, UNI_B) == 2);
			assert(getKPIpoints(g, UNI_C) == 2);
			assert(getStudents(g, UNI_C, STUDENT_BPS) == 2);
			assert(getStudents(g, UNI_C, STUDENT_BQN) == 2);

			assert (getARC(g, exampleActionMatt.destination) == ARC_C);
		} 

		assert(getMostPublications(g) == NO_ONE);

		throwDice(g, diceScore);
	}


	printf("The getKPI and getMostPublications test passed!\n");


	//Test isLegalAction false & the PASS action

	exampleActionMatt.destination[] = {'B','\0'};
	assert(isLegalAction(g,exampleActionMatt) == FALSE);
	exampleActionMatt.destination[] = {'L', 'L', 'L', '\0'};
	assert(isLegalAction(g,exampleActionMatt) == FALSE);
	exampleActionMatt.actionCode = BUILD_GO8;
	assert(isLegalAction(g,exampleActionMatt) == FALSE);
	exampleActionMatt.actionCode = START_SPINOFF;
	assert(isLegalAction(g,exampleActionMatt) == FALSE);
	exampleActionMatt.actionCode = RETRAIN_STUDENTS;
	assert(isLegalAction(g,exampleActionMatt) == FALSE);
	exampleActionMatt.actionCode = PASS;
	assert(isLegalAction(g,exampleActionMatt) == TRUE);

	printf("isLegalAction tests passed!\n");


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
	 * disposeGame to getMostArcs		   Paulus
	 * getMostPublications to getKPIpoints  Matt
	 * getArcs to end					   Sijia
	 */

	disposeGame(g);
	printf("All tests Passed");
}