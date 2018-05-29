#include <stdio.h>

//Function Prototyping
void printCircumflexAccents (int numLows);

int main()
{
	//Declaration of the variable that will store userinput
	int userInputNum;
	
	//Prompting User to type input
	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &userInputNum);
	
	//Function that prints a triangle
	printCircumflexAccents(userInputNum);
}



void printCircumflexAccents (int numLows) 
{
	for (int currentRow=1; currentRow<=numLows; currentRow++){
		
		/*First Row
		     ^  <--Printing this case
		  ^   ^
		^^^^^		*/
		if(currentRow==1)
		{
			for(int j=1; j<numLows; j++) //loop that prints numLows-1 spaces on the left-side of ^
			{
				printf(" ");
			}
			printf("%c\n",'^');
		}
		
		/*Last row
			 ^
		  ^   ^
		^^^^^ <---- Printing this case  */
		else if(currentRow==numLows)
		{
			int numAccLastLine = (2*numLows)-1;
			for(int k=1;k<=numAccLastLine;k++) //loop that prints (2*numLows)-1 of ^
			{
				printf("%c",'^');
			}
			
			printf("\n");
		}
		
		//Rows other than the first & last
		/*  ^
		  ^   ^    <----- Printing these cases
		^^^^^     */
		else
		{
			for(int m=1;m<=(numLows-currentRow);m++) //i-th line: n-i spaces on the left side of ^
			{
				printf(" ");
			}
			printf("%c",'^');
			
			int numSpacesBetween = (2*(currentRow-1))-1; //i-th line: number of spaces between ^'s is equal to (2*(currentRow-1))-1
			for(int n=1;n<=numSpacesBetween;n++) //Loop that prints spaces in between ^'s
			{
				printf(" ");
			}
			printf("%c\n",'^');
		}
	}
}
