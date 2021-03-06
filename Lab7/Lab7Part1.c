#include <stdio.h>
#include <stdbool.h>

char board[26][26];
int n;  //global variable

void initializeBoard();

void printBoard();

char oppColour(char colour);

bool isUorColour(char position, char colour);

bool areColAndRow0(int deltaRow, int deltaCol);

bool positionInBounds(char row, char col);

bool checkLegalInDirection(char row, char col, char colour, int deltaRow, int deltaCol);

void moveAndFlip(char row, char col, char colour);

bool isPosLegal(char row, char col, char colour);

int flipCount(char row, char col, char colour);

bool moveAvail(char colour);

char figureOutWinner();

void computerMove(char colour);

/*End of Functions*/


int main(){
	
	/*Ask user for board dimension*/
	printf("Enter the board dimension: ");
	scanf("%d", &n);


	/*Set which colour computer will play and user's colour*/
	char compColour;
	printf("Computer plays (B/W) : ");
	scanf(" %c", &compColour);
	char userColour = oppColour(compColour);
	
	/*Initialize Board*/
	initializeBoard();
	printBoard();


	char turn = 'B'; //initial turn
	while(	moveAvail(compColour) || moveAvail(userColour)	){ //while game is not over
		char row, col;
		
		if(turn == compColour){ //Computer's Turn
			computerMove(compColour);
			printBoard();
		}
		else{//User's Turn
			printf("Enter move for colour %c (RowCol): ", userColour);
			scanf(" %c%c", &row, &col);
			if(	!positionInBounds(row, col)	|| !isPosLegal(row, col, userColour) ){ //Invalid input is entered by user
					printf("Invalid move.\n");
					printf("%c player wins.\n", oppColour(userColour));
					return 0;
			}
			else{//Valid input is entered by user
				moveAndFlip(row, col, userColour);
				printBoard();
			}
		}/*End of the else*/
		
		/* Check if the game is to be ended or not */
		if(	moveAvail(compColour) || moveAvail(userColour)	){ 
			if(		moveAvail(	oppColour(turn)	)	)
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
			board[i][j] = 'U';
	}
	
	board[(n/2)-1][(n/2)-1] ='W';
	board[(n/2)-1][n/2] = 'B';
	board[n/2][(n/2)-1] = 'B';
	board[n/2][n/2] = 'W';
	
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
	int i;
	for(i=0; i<n; i++, columnCoordinate++){
		printf("%c ", columnCoordinate); //notice a space after the configuration each row
		int j;
		for(j=0; j<n; j++){
			printf("%c", board[i][j]);
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

bool checkLegalInDirection(char row, char col, char colour, int deltaRow, int deltaCol){
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

void moveAndFlip(char row, char col, char colour){ //Flip appripriate tiles
	int deltaRow;
	int deltaCol;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol) &&
				checkLegalInDirection(row, col, colour, deltaRow, deltaCol)){
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

bool isPosLegal(char row, char col, char colour){ //Evaluate if a position that is being made is legal or not
	int deltaRow;
	int deltaCol;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol) &&
				checkLegalInDirection(row, col, colour, deltaRow, deltaCol) ){
					return true;
			}
		}
	}
	return false;
}

int flipCount(char row, char col, char colour){ //Counts how many tiles can be flipped if a move is made at the position of board[row][col]
	int deltaRow, deltaCol;
	int colourCount = 0;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol) &&
				checkLegalInDirection(row, col, colour, deltaRow, deltaCol)){
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

bool moveAvail(char colour){//Check if there is any available move for the colour
	char row, col;
	for(row='a'; row<n+'a'; row++){
		for(col='a'; col<n+'a'; col++){
				int deltaRow;
				for(deltaRow=-1; deltaRow<=1; deltaRow++){
					int deltaCol;
					for(deltaCol=-1; deltaCol<=1; deltaCol++){
						if(!areColAndRow0(deltaRow, deltaCol) &&
							checkLegalInDirection(row, col, colour, deltaRow, deltaCol) ){
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
			if(board[row - 'a'][col - 'a'] == 'B'){
				countB ++;
			}
			else if(board[row - 'a'][col - 'a'] == 'U'){
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

void computerMove(char colour){//Computer makes a move
	int highestScore = 0;
	int computedScore = 0;
	char row, col, currentRow, currentCol, highestRow, highestCol;
	for(row = 'a'; row < 'a' + n; row++){
		for(col = 'a'; col <'a' + n;  col++){
			if(isPosLegal(row, col, colour) ){
				computedScore = flipCount(row, col, colour);
				currentRow = row;
				currentCol = col;
			}
			
			if(computedScore > highestScore){
				highestScore = computedScore;
				highestRow = currentRow;
				highestCol = currentCol;
			}
		}
	}
	moveAndFlip(highestRow, highestCol, colour);
	printf("Computer places %c at %c%c\n", colour, highestRow, highestCol);
}
