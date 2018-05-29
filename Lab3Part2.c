#include <stdio.h>

int main()
{
	//Declaring variables
	double firstNumber, secondNumber, res;
	char operator;
	
	//Prompting user to input values
	printf("Enter first number: ");
	scanf("%lf", &firstNumber);
	
	printf("Enter second number: ");
	scanf("%lf", &secondNumber);
	
	printf("Enter calculation command (one of a, s, m, or d): ");
	scanf(" %c", &operator);
	
	
	
	if(operator=='a') //addition
	{
		res=firstNumber+secondNumber;
		printf("Sum of %.2lf and %.2lf is %.2lf\n", firstNumber, secondNumber, res);
	}
	else if(operator=='s') //subtraction
	{
		res=firstNumber-secondNumber;
		printf("Difference of %.2lf from %.2lf is %.2lf\n", firstNumber, secondNumber, res);
	}
	else if(operator=='m') //multiplication
	{
		res=firstNumber*secondNumber;
		printf("Product of %.2lf and %.2lf is %.2lf\n", firstNumber, secondNumber, res);
	}
	else if(operator=='d') //division
	{
		if(secondNumber!=0) //Ensuring divisor is not zero
		{
		res=firstNumber/secondNumber;
		printf("Division of %.2lf by %.2lf is %.2lf\n", firstNumber, secondNumber, res);
		}
		else
			printf("Error, trying to divide by zero\n"); //Warning that divisor is zero
	}
	else //case of where user input does not belong to any one of addition, subtraction, multiplication, and division
		printf("Error, unknown calculation command given\n");
		
	return 0;
}
