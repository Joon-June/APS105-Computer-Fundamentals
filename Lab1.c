#include <stdio.h>
#include <math.h>

int main(){
	
	//declaring variables
	double inputNum1,inputNum2,inputNum3,X,Y,Z,mean,stdev; 

	//Prompt user to type numbers & scan the values
	printf("Enter three numbers: ");
	scanf("%lf %lf %lf", &inputNum1, &inputNum2, &inputNum3); 
	
	//calculating mean
	mean=(inputNum1+inputNum2+inputNum3)/3; 
	
	//calculating standard deviation
	X= pow(mean-inputNum1,2);
	Y=pow(mean-inputNum2,2);
	Z=pow(mean-inputNum3,2);
	stdev=sqrt((X+Y+Z)/2);
	
	//Show values of mean & standard deviation to the user
	printf("The mean is %.2lf and the standard deviation is %.2lf\n",mean,stdev);
	
	return 0;
	
}
