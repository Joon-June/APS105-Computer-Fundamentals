#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isUorColour(char position, char colour);
bool areColAndRow0(int deltaRow, int deltaCol);
bool isExclamationMark (char colour, char row, char col);
bool positionInBounds(int n, char row, char col);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
void changeBoardConfiguration(char colour, char row, char col);
void printBoard(char board[][26], int n);
void moveAndFlip(char board[][26], char row, char col, char colour, int deltaRow, int deltaCol);


int main(){
	int n;
	char colour;
	char row;
	char col;
	
		//First part
	/*print board configuration (static 2D array) based on the value of "boardSize"
		-  only 4 points at very middle of the board are B or W
		-  All the other points are U*/
		
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	char board[26][26];
	
	if(n<27){
		int i;
		for(i=0; i<n; i++){
			int j;
			for(j=0; j<n; j++)
				board[i][j] = 'U';
		}
		
		board[(n/2)-1][(n/2)-1] ='W';
		board[(n/2)-1][n/2] = 'B';
		board[n/2][(n/2)-1] = 'B';
		board[n/2][n/2] = 'W';
		
		printBoard(board, n);
	}
	else return 0;

	
	
	/*Second Part*/
	printf("Enter board configuration: \n");
	do{
		scanf(" %c%c%c", &colour, &row, &col);
		board[row-'a'][col-'a'] = colour;
	}while(!isExclamationMark(colour, row, col));
	
	printBoard(board, n);



	//Third Part
	printf("Available moves for W:\n");

	for(row='a'; row<n+'a'; row++){
		for(col='a'; col<n+'a'; col++){
			int deltaRow;
			for(deltaRow=-1; deltaRow<=1; deltaRow++){
				int deltaCol;
				for(deltaCol=-1; deltaCol<=1; deltaCol++){
					
					if(!areColAndRow0(deltaRow, deltaCol)){
						if(checkLegalInDirection(board, n, row, col, 'W', deltaRow, deltaCol)){
							printf("%c%c\n", row, col);
							deltaRow = 2;
							break;
						}
					}
				}
			}
		}
	}
	
	
	
	
	printf("Available moves for B:\n");
	
	for(row='a'; row<n+'a'; row++){
		for(col='a'; col<n+'a'; col++){
			int deltaRow;
			for(deltaRow=-1; deltaRow<=1; deltaRow++){
				int deltaCol;
				for(deltaCol=-1; deltaCol<=1; deltaCol++){
					if(!areColAndRow0(deltaRow, deltaCol)){
						if(checkLegalInDirection(board, n, row, col, 'B', deltaRow, deltaCol)){
							printf("%c%c\n", row, col);
							deltaRow = 2;
							break;
						}
					}
				}
			}
		}
	}
	
	

	
	/*Fourth Part*/
	printf("Enter a move: \n");
	scanf(" %c%c%c", &colour, &row, &col);
	

	/*Fifth Part*/
	int deltaRow;
	int numAvailDirec=0;
	for(deltaRow=-1; deltaRow<=1; deltaRow++){
		int deltaCol;
		for(deltaCol=-1; deltaCol<=1; deltaCol++){
			if(!areColAndRow0(deltaRow, deltaCol)){
				if(checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
					numAvailDirec++;
					
					moveAndFlip(board, row, col, colour, deltaRow, deltaCol);
				}
			}
		}
	}
			
	if(numAvailDirec == 0)	printf("Invalid Move.\n");
	else{
		board[row-'a'][col-'a'] = colour;
		printf("Valid Move.\n");
	}

	printBoard(board, n);
}



/*Function Lists*/

bool isExclamationMark (char colour, char row, char col){
	if(colour == '!' && row == '!' && col == '!')
		return true;
	else
		return false;
}



bool positionInBounds(int n, char row, char col){
	if(row >= 'a' && row < n+'a' && 
		col >= 'a' && col < n+'a')
		return true;
	else
		return false;
}



bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
	char currentPos = board[row-'a'][col-'a'];
	if(currentPos =='U'){
		char movedRow = row + deltaRow;
		char movedCol = col + deltaCol;
		char movedPosition = board[movedRow-'a'][movedCol-'a'];
		
		/*If  first moved position is other colour */
		if(positionInBounds(n, movedRow, movedCol) && !isUorColour(movedPosition, colour)){
			int i;
			for(i=2; ; i++){
				char moveFurtherRow = row + (i*deltaRow);
				char moveFurtherCol = col + (i*deltaCol);
				char furtherMovedPosition = board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)];
									
				if(positionInBounds(n, moveFurtherRow, moveFurtherCol)){
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




bool areColAndRow0(int deltaRow, int deltaCol){
	if(deltaRow == 0 && deltaCol==0)
		return true;
	else
		return false;
}



bool isUorColour(char position, char colour){
	if(position == 'U' || position == colour)
		return true;
	else
		return false;
}



void printBoard(char board[][26], int n){
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



void moveAndFlip(char board[][26], char row, char col, char colour, int deltaRow, int deltaCol){
	int i;
	for(i=1; ; i++){
		char furtherMovedPosition = board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)];
							
		if(!isUorColour(furtherMovedPosition, colour)){
			board[row-'a'+(i*deltaRow)][col-'a'+(i*deltaCol)] = colour;
		}
		else if(furtherMovedPosition == colour) break;
	}
}
