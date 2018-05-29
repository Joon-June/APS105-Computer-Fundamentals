#include <stdio.h>

int main()
{
	//Declaring variables that will be used
	int amountInCent, numQuarter, numDime, numNickel, numCent;
	int quarterRemainder, dimeRemainder;
	
	printf("Please give an amount in cents less than 100: \n");
	scanf("%d", &amountInCent);
	
	while(amountInCent>0 && amountInCent<100)
	{/*Since integer types exclude decimal parts, quotient of dividing user input by 25 is a number of quarters required. 
	 A quotient of dividing a remainder of the division by 10 is a number of dimes required and so forth. */
	 
		numQuarter = amountInCent/25; //number of quarters required
		quarterRemainder = amountInCent%25; 
		numDime = quarterRemainder/10; //number of dimes required
		dimeRemainder = quarterRemainder%10;
		numNickel = dimeRemainder/5; //number of nickels required
		numCent = dimeRemainder%5; //number of cents required
		
		
	
		if(numQuarter>0) //Only if number of quarters is greater than 0, the program will print corresponding output
		{
			printf("%d quarter", numQuarter);
			
			if(numQuarter>1) //Decision whether to put "s" the next
				printf("s");
				
			if(numDime == 0 && numNickel == 0 && numCent ==0) //Decision whether to put a period or comma
				printf(".");
			else
				printf(", ");
		}
		
		
		
		if(numDime>0) //Only if number of dimes is greater than 0, the program will print corresponding output
		{
			printf("%d dime", numDime);
			
			if(numDime>1) //Decision whether to put "s" the next
				printf("s");
			
			if(numNickel == 0 && numCent ==0) //Decision whether to put a period or comma
				printf(".");
			else
				printf(", ");
		}
	
	
	
		if(numNickel>0) //Only if number of dimes is greater than 0, the program will print corresponding output
		{
			printf("%d nickel", numNickel);
			
			if(numNickel>1) //Decision whether to put "s" the next
				printf("s");
			
			if(numCent == 0) //Decision whether to put a period or comma
				printf(".");
			else
				printf(", ");
		}
		
		
		
		if(numCent>0) //Only if number of dimes is greater than 0, the program will print corresponding output
		{
			printf("%d cent", numCent);
			if(numCent>1) //Decision whether to put "s" the next
				printf("s.");
			else
				printf(".");
		}
		
		printf("\n");
		
		//Prmpting user input for the next change calculation
		printf("Please give an amount in cents less than 100: \n"); 
		scanf(" %d", &amountInCent);
	}
	//If the user input is not true for the condition for the while loop, the program will print "Goodbye"
	printf("Goodbye.\n");
	
	return 0;
}
