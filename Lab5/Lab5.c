#include <stdio.h>

//Function Prototyping
void triangle(int numRows);
int choose(int n, int r);
int factorial(int n);


int main()
{
	int numRows; //Number of rows that an user wants
	
	do
	{
		printf("Enter the number of rows: "); //
		scanf("%d", &numRows);
		
		if(numRows>=0)
			{
				triangle(numRows);
			}
		else	
			break;
	}
	while(1);
	
	return 0;
}

int factorial(int n)
{
	int factorialOutput=1;
	for(; n>0; n--)
	{
		factorialOutput *=n;
	}
	return factorialOutput;
}

int choose(int n, int r)
{
	int combOutput;
	combOutput = factorial(n)/(factorial(r)*factorial(n-r));
	return combOutput;
}


void spaces(int numSpaces)
{
	for(; numSpaces>0; numSpaces--) //print spaces of 3*numSpaces
	{
		printf("   "); //3spaces = one unit (because one number occupies 3 spaces)
	}
}



void triangle(int numRows)
{
	int currentRow;
	for(currentRow=0; numRows>0; currentRow++, numRows--)
	{
		spaces(numRows-1); //
		int r;
		for(r=currentRow; r>=0; r--)
		{
			printf("%-3d", choose(currentRow, r));
			if(r==0)
				printf("\n");
			else
				spaces(1);
		}
	}
}
