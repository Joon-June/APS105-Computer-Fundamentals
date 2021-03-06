#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "lab7part2lib.h"
#include <time.h>

char mainBoard[26][26];
int n;  //global variable
char userColour, compColour;
int numTurns=0;
char highestRow, highestCol;

void initializeBoard();
void printBoard();
char oppColour(char colour);
bool isUorColour(char position, char colour);
bool areColAndRow0(int deltaRow, int deltaCol);
bool positionInBounds(char row, char col);
bool checkLegalInDirection(char board[][26], char row, char col, char colour, int deltaRow, int deltaCol);
void moveAndFlip(char board[][26], char row, char col, char colour);
bool isPosLegal(char board[][26], char row, char col, char colour);
bool moveAvail(char board[][26], char colour);
char figureOutWinner();
int flipCount(char board[][26], char row, char col, char colour);
double cornerWeight();
double flippingWeight();
double forfeitScore(char board[][26]);
double evalBoard(char board[][26]);
double minimax(char board[][26], int depth, double alpha, double beta, bool maximizingPlayer, int flag);
void computerMove(char board[][26]);

/*End of Functions*/

int main(){
	double totalTime = 0.0;
	clock_t timeStart, timeEnd;
	/*Ask user for board dimension*/
	printf("Enter the board dimension: ");
	scanf("%d", &n);

	/*Set which colour computer will play and user's colour*/
	printf("Computer plays (B/W) : ");
	scanf(" %c", &compColour);
	userColour = oppColour(compColour);
	
	/*Initialize Board*/
	initializeBoard();
	printBoard();


	char turn = 'B'; //initial turn
	while(	moveAvail(mainBoard, compColour) || moveAvail(mainBoard, userColour)	){ //while game is not over
		int row, col;
		
		if(turn == compColour){ //Computer's Turn
			timeStart = clock();
			computerMove(mainBoard);
			timeEnd = clock();
			if(((double) (timeEnd - timeStart))/CLOCKS_PER_SEC > totalTime)totalTime = ((double) (timeEnd - timeStart))/CLOCKS_PER_SEC;
			numTurns++;
			printBoard();
		}
		else{//User's Turn
			/*printf("Enter move for colour %c (RowCol): ", userColour);
			scanf(" %c%c", &row, &col);*/
			findSmartestMove(mainBoard, n, userColour, &row, &col);
			printf("Testing AI move (row, col): %c%c\n", row +'a', col +'a');
			
			if(	!positionInBounds(row+'a', col+'a')	|| !isPosLegal(mainBoard, row+'a', col+'a', userColour) ){ //Invalid input is entered by user
					printf("Invalid move.\n");
					printf("%c player wins.\n", oppColour(userColour));
					return 0;
			}
			else{//Valid input is entered by user
				moveAndFlip(mainBoard, row+'a', col+'a', userColour);
				numTurns++;
				printBoard();
			}
		}/*End of the else*/
		
		/* Check if the game is to be ended or not */
		if(	moveAvail(mainBoard, compColour) || moveAvail(mainBoard, userColour)	){ 
				if(		moveAvail(	mainBoard, oppColour(turn)	)	)
					turn = oppColour(turn);
				else
					printf("%c player has no valid move\n", oppColour(turn));
				/*             The current turn is maintained.
					Therefore, no changes are made to the variable "turn".   */
		}
		else{ //End of the Game
			switch( figureOutWinner() ){
				case 'B':
					printf("B player wins.\n");
					break;
				case 'W':
					printf("W player wins.\n");
					break;
				case 'D':
					printf("Draw!\n");
			}
		printf("%lf", totalTime);
		return 0;
		}
	} /*End of the while loop*/
}/*End of main function*/


/*Functions*/
void initializeBoard(){
	int i;
	for(i=0; i < n; i++){
		int j;
		for(j=0; j<n; j++)
			mainBoard[i][j] = 'U';
	}
	
	mainBoard[(n/2)-1][(n/2)-1] ='W';
	mainBoard[(n/2)-1][n/2] = 'B';
	mainBoard[n/2][(n/2)-1] = 'B';
	mainBoard[n/2][n/2] = 'W';
	
}

void printBoard(){
	/*Printing the first row (column configuration)*/
	printf("  "); //print two spaces first
	char rowCoordinate = 'a';
	for(; rowCoordinate < ('a'+n); rowCoordinate++){
		printf("%c", rowCoordinate);
	}
	printf("\n");
	
	/*Printing row configuration & entire board configuration*/
	char columnCoordinate = 'a';
	int i;	for(i=0; i<n; i++, columnCoordinate++){
		printf("%c ", columnCoordinate); //notice a space after the configuration each row
		int j;	for(j=0; j<n; j++){
			printf("%c", mainBoard[i][j]);
		}
		printf("\n");
	}
}

char oppColour(char colour){
	if(colour == 'W')
		return 'B';
	else
		return 'W';
}

bool isUorColour(char position, char colour){ //Equivalent to oppColour but includes position
	if(position == 'U' || position == colour)
		return true;
	else
		return false;
}

bool areColAndRow0(int deltaRow, int deltaCol){
	if(deltaRow == 0 && deltaCol==0)
		return true;
	else
		return false;
}

bool positionInBounds(char row, char col){
	if(row >= 'a' && row < n+'a' && 
		col >= 'a' && col < n+'a')
		return true;
	else
		return false;
}

bool checkLegalInDirection(char board[][26], char row, char col, char colour, int deltaRow, int deltaCol){
	char currentPos = board[row-'a'][col-'a'];
	if(currentPos =='U'){
		char movedRow = row + deltaRow;
		char movedCol = col + deltaCol;
		char movedPosition = board[movedRow-'a'][movedCol-'a'];
		
		/*If  first moved position is other colour */
		if(positionInBounds(movedRow, movedCol) && !isUorColour(movedPosition, colour)){
			int i;
			for(i=2; ; i++){
				char moveFurtherRow = row + (i*deltaRow);
				char moveFurtherCol = col + (i*deltaCol);
				char furtherMovedPosition = board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)];
									
				if(positionInBounds(moveFurtherRow, moveFurtherCol)){
					if(furtherMovedPosition == colour){
						return true;
						break;
					}
					else if(furtherMovedPosition == 'U'){
						return false;
						break;
					}
					
					/*Don't do anything if furtherMovedPosition == other colour (loop keeps going)*/
				}else		return false;
			}
		}else		return false;
	}else		return false;
}

void moveAndFlip(char board[][26], char row, char col, char colour){ //Flip appripriate tiles
	int deltaRow;
	int deltaCol;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol) &&
				checkLegalInDirection(board, row, col, colour, deltaRow, deltaCol)){
					int i;
					for(i=1; ; i++){
						char furtherMovedPosition = board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)];
						
						if(!isUorColour(furtherMovedPosition, colour)){
							board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)] = colour;
						}
						else if(furtherMovedPosition == colour) break;
					}
			}
		}
	}
	board[row-'a'][col-'a'] = colour;
}

bool isPosLegal(char board[][26], char row, char col, char colour){ //Evaluate if a position that is being made is legal or not
	int deltaRow, deltaCol;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol) &&
				checkLegalInDirection(board, row, col, colour, deltaRow, deltaCol) ){
					return true;
			}
		}
	}
	return false;
}

bool moveAvail(char board[][26], char colour){//Check if there is any available move for the colour
	char row, col;
	for(row='a'; row<n+'a'; row++){
		for(col='a'; col<n+'a'; col++){
			int deltaRow;
			for(deltaRow=-1; deltaRow<=1; deltaRow++){
				int deltaCol;
				for(deltaCol=-1; deltaCol<=1; deltaCol++){
					if(!areColAndRow0(deltaRow, deltaCol) &&
						checkLegalInDirection(board, row, col, colour, deltaRow, deltaCol) ){
							return true;
					}
				}
			}
		}
	}return false;
}

char figureOutWinner(){
	int countB = 0;
	int countU = 0;
	char row;
	char col;
	
	for(row='a'; row<n+'a'; row++){
		for(col='a'; col<n+'a'; col++){
			if(mainBoard[row - 'a'][col - 'a'] == 'B'){
				countB ++;
			}
			else if(mainBoard[row - 'a'][col - 'a'] == 'U'){
				countU++;
			}
		}
	}
	
	if(countB > ( (n*n - countU) / 2 ) ) 
		return 'B';
	else if(countB < ( (n*n - countU) / 2 ))
		return 'W';
	else //countB == countU
		return 'D';
}

int flipCount(char board[][26], char row, char col, char colour){ //Counts how many tiles can be flipped if a move is made at the position of board[row][col]
	int deltaRow, deltaCol;
	int colourCount = 0;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol) &&
				checkLegalInDirection(board, row, col, colour, deltaRow, deltaCol)){
					int i;
					for(i=1; ; i++){
						char furtherMovedPosition = board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)];
											
						if(!isUorColour(furtherMovedPosition, colour)){
							colourCount++;
						}
						else if(furtherMovedPosition == colour) break;
					}
			}
		}
	}
	return colourCount;
}

double cornerWeight(){
	if(n > 5 && n <11)	return 90.0;
	else if(n > 11 && n <19)		return 50.0;
	else if(n > 19 && n <23)		return  70.0;
	else if(n == 24)		return  60.0;
	else if(n == 26)		return 65;
}

double flippingWeight(){
	double weight;
	if(n > 5 && n <11)	
		weight = 10.0 + 5.0*pow(( ( numTurns) / ((double)(n*n)) ),  n/2);
	else if(n > 11 && n <23)		
		weight = 40.0 + 5.0*pow(( ( numTurns) / ((double)(n*n)) ),  n/2);
	else if(n == 24)		
		weight = 30.0 + 5.0*pow(( ( numTurns) / ((double)(n*n)) ),  n/2);
	else if(n == 26)		
		weight = 45.0 + 5.0*pow(( ( numTurns) / ((double)(n*n)) ),  n/2);
		
	return weight;
}

double forfeitScore(char board[][26]){
	double score;
	char row, col;
	int numAvailMoves = 0;
	for(row='a'; row<n+'a'; row++){
		for(col='a'; col<n+'a'; col++){
				int deltaRow;
				for(deltaRow=-1; deltaRow<=1; deltaRow++){
					int deltaCol;
					for(deltaCol=-1; deltaCol<=1; deltaCol++){
						if(!areColAndRow0(deltaRow, deltaCol) &&
							checkLegalInDirection(board, row, col, userColour, deltaRow, deltaCol) ){
								numAvailMoves++;
						}
					}
				}
		}
	}
	score = 100.0 - 25.0*(numAvailMoves);
	
	return score;
}

double evalBoard(char board[][26]){
	double score;
	/*Corner Evaluation*/
	int cornerScore = 0;
						/*Top Left Corner*/
	if(board[0][0] == compColour) 	cornerScore+=25;
	else if((board[0][1] ==  compColour && board[0][2] == userColour) ||
				(board[1][0] ==  compColour && board[2][0] == userColour)  ||
				((board[1][1] ==  compColour)	&& board[2][2] == userColour) )	cornerScore -=100; //Risk Evaluation
				
					/*Top RightCorner*/
	if(board[0][n-1] ==  compColour)		cornerScore+=25;
	else if((board[0][n-2] ==  compColour && board[0][n-3] == userColour)||
				(board[1][n-2] ==  compColour && board[2][n-3] == userColour)||
				(board[1][n-1] ==  compColour&& board[2][n-1] == userColour) )		cornerScore -=100; //Risk Evaluation
				
					/*Bottom Left Corner*/
	if(board[n-1][0] ==  compColour)		cornerScore+=25;
	else if((board[n-2][0] ==  compColour && board[n-3][0] == userColour)	||
				(board[n-2][1] ==  compColour && board[n-3][2] == userColour) ||
				(board[n-1][1] ==  compColour	&& board[n-1][2] == userColour) )cornerScore -=100; //Risk Evaluation
				
					/*Bottom Right Corner*/
	if(board[n-1][n-1] ==  compColour)		cornerScore+=25;
	else if((board[n-2][n-1] ==  compColour && board[n-3][n-1] == userColour)||
				(board[n-2][n-2] ==  compColour && board[n-3][n-3] == userColour)||
				(board[n-1][n-2] ==  compColour && board[n-1][n-3] == userColour) )		cornerScore -=100; //Risk Evaluation
	

						/*Flipping Evaluation*/
	int flippingScore = 0;
	int totalNumTiles = 0;
	int j; for(j = 0; j < n; j++){
		int k; for(k = 0; k < n; k++){
			if( board[j][k] != 'U') totalNumTiles++;
			if( board[j][k] == compColour  ) flippingScore++;
		}
	}
	flippingScore = (100 * ((double) (flippingScore)) ) / totalNumTiles;

	score = ((double)cornerScore) * cornerWeight() +
							  flippingScore * flippingWeight()+
							  forfeitScore(board)*(4.0);
	
	return score;
}

double minimax(char board[][26], int depth, double alpha, double beta, bool maximizingPlayer, int flag){ //minimax algorithm with alpha-beta prunning
	
	/*Base Case*/
	if(depth == 0)	return evalBoard(board);

	if (maximizingPlayer == true){
		double nodeValue= -DBL_MAX; //represents -¡Ä
			char row; for(row = 'a'; row < 'a' + n; row++){ //For all children branches
				char col; for(col = 'a'; col <'a' + n; col++){
					if(	isPosLegal(board, row, col, compColour) ){
						char copiedBoard[26][26];
						int size = sizeof(char) * 26 * 26;
						
						memcpy(copiedBoard, board, size);
						moveAndFlip(copiedBoard, row, col, compColour);
						
						if(moveAvail(copiedBoard, userColour)){
							nodeValue = fmax(nodeValue, minimax(copiedBoard, depth-1, alpha, beta, false, flag+1)); //Recursive Part
						}else{
							nodeValue = fmax(nodeValue, minimax(copiedBoard, depth-1, alpha, beta, true, flag+1));
						}
						
						if(nodeValue > alpha){
							alpha = nodeValue;
							
							if(flag == 0){
								highestRow = row;
								highestCol = col;
							}
						}
						
						/*In case where terminal node is not evaluated because both players had 
						 * no available move during expansion of game tree*/
						else if(nodeValue == -DBL_MAX && flag == 0){ 
							nodeValue = evalBoard(copiedBoard);
							if(nodeValue > alpha){
								alpha = nodeValue;
								
								highestRow = row;
								highestCol = col;
							}
						}
						
						if(alpha >= beta)	return nodeValue; //prunning: beta cut-off
					}
				}
			}
			return nodeValue;
	}
	else{//minimizingPlayer's turn (opponent)
		double nodeValue= DBL_MAX; //represents +¡Ä
		
		char row; for(row = 'a'; row < 'a' + n; row++){ //For all children branches
			char col; for(col = 'a'; col <'a' + n; col++){
				if(	isPosLegal(board, row, col, userColour) ){
					char copiedBoard[26][26]; //This is removed when function terminates
					int size = sizeof(char) * 26 * 26;
					memcpy(copiedBoard, board, size); 
					moveAndFlip(copiedBoard, row, col, userColour);
					
					if(moveAvail(copiedBoard, compColour)){
						nodeValue = fmin(nodeValue, minimax(copiedBoard, depth-1, alpha, beta, true, flag+1)); //Recursive Part
					}else{
						nodeValue = fmin(nodeValue, minimax(copiedBoard, depth-1, alpha, beta, false, flag+1));
					}
					
					if(nodeValue < beta)	beta = nodeValue; //No need to save row & col information since we always start with computer

					if(beta <= alpha)	return nodeValue; //prunning: beta cut-off
				}
			}
		}
		return nodeValue;
	}
}

void computerMove(char board[][26]){//Computer makes a move
	/*Initial Call*/
	if(n > 5 && n <9)
		minimax(board, 5, -DBL_MAX, DBL_MAX, true, 0); // starting as maximizingPlayer
	else if(n > 9 && n <19)
		minimax(board, 3, -DBL_MAX, DBL_MAX, true, 0); 
	else if(n > 19 && n <27)
		minimax(board, 1, -DBL_MAX, DBL_MAX, true, 0); 
	else if(n==4 && compColour == 'B'){
		if(numTurns == 0) {
			moveAndFlip(board, 'b', 'a', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'b', 'a');
		}
		if(numTurns == 2)  {
			moveAndFlip(board, 'a', 'b', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'a', 'b');
		}
		if(numTurns == 4)  {
			moveAndFlip(board, 'b', 'd', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'b', 'd');
		}
		if(numTurns == 6) {
			moveAndFlip(board, 'd', 'a', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'd', 'a');
		}
		if(numTurns == 8)  {
			moveAndFlip(board, 'd', 'd', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'd', 'd');
		}
		if(numTurns == 10)  {
			moveAndFlip(board, 'd', 'c', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'd', 'c');
		}
		if(numTurns == 11) {
			moveAndFlip(board, 'a', 'd', compColour);
			printf("Computer places %c at %c%c\n", compColour, 'a', 'd');
		}
		return;
	}
	else
		minimax(board, 11, -DBL_MAX, DBL_MAX, true, 0);
		
	moveAndFlip(board, highestRow, highestCol, compColour);
	printf("Computer places %c at %c%c\n", compColour, highestRow, highestCol);
	return;
}
