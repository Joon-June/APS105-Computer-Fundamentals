#include <stdio.h>
#include <math.h>

int convertDecimalToBinary (int userInput);
int convertBinaryToDecimal (int userInput);

int main()
{
	//Declaration of variables
	/*numRun describes the number of times user repeated program. 
	   It also indicates user how many times he/she has repeated*/
	
	char binaryOrDecimal;
	int userInputNum;
		
	do
	{	//Prompting user which input to choose
		printf("Enter B for conversion of Binary to Decimal, OR\n");
		printf("Enter D for conversion of Decimal to Binary: ");
		scanf(" %c",&binaryOrDecimal);
		printf("Enter your number: ");
		
		
		/*Following if statements evaluate user input and sort out invalid input
		   By using '||' operand, the efficiency of program  is improved*/
		   
		if(binaryOrDecimal=='B' || binaryOrDecimal=='D')
		{
			scanf("%d", &userInputNum); //Program will scan numerical input only if user inputs an valid input
				
				//Since user chooses either B or D, 
				//Decided to use switch statement instead of if statements to make program more intuitive and legible
				switch (binaryOrDecimal)
				{
				case 'B':
					printf("%d in binary = %d in decimal\n", userInputNum, convertBinaryToDecimal(userInputNum));
					break;
					
				case 'D':
					printf("%d in decimal = %d in binary\n",userInputNum, convertDecimalToBinary(userInputNum));
					break;
				}
		}
		else
		{
			printf("Invalid input; Goodbye\n");
		}
		
	}
	while(1);
}

int convertDecimalToBinary (int userInput)
{
	int binaryOutput; 														//Declared before the loop to be able to print the output after the conversion. (Scope issue)
	
	//Conversion from decimal to binary
	for(int nthDigit=0; userInput!=0; nthDigit++) 		   //divides user input by 2 (binary) until userinput = 0
	{
		int onesDigit = userInput %2; 							   //divide user input by 2 to obtain a digit of binary number: 
																					   //e.g. [3 = 2^1 + 2^0],  [3%2 = 1], obtained value 1 is mutiplied by 10^(nthDigit)
		binaryOutput += (onesDigit * pow(10, nthDigit)); //add the value obtained by calculating remainder on binaryOutput
		userInput /= 2; 													   //assign userInput newly after obtaining a digit of binary number to obtain the next
	}
	
	return binaryOutput; 												  //returns conversion result
}

int convertBinaryToDecimal (int userInput)
{
	int decimalOutput;													   //Declared before the loop to be able to print the output after the conversion. (Scope issue)
	
	//Conversion from binary to decimal
	for(int nthDigit=0; userInput!=0; nthDigit++)		    //divides user input by 10 (decimal) until userinput=0
	{
		int onesDigit = userInput % 10; 							    //Obtains a digit from user input, starting from ones digit
		decimalOutput += (onesDigit * pow(2, nthDigit)); //In case of 101, the first loop will evaluate 1*(2^0), which is 1
		userInput /= 10; 													    //assigns userInput newly after taking off a digit
	}
		
	return decimalOutput;													//returns conversion result
}	
