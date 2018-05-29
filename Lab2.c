#include <stdio.h>
 
int main()
{
	//Declaration of variables
    char band1, band2, band_m, band_t;
	int b1, b2, twoDigit;
	double b_m, b_t, resistance, resistanceForPrint;
	
	/*Prompting a user to type band colours*/
	printf("Please enter the 1st band: \n");
	scanf("%c", &band1); //first band
    
	printf("Please enter the 2nd band: \n");
	scanf( " %c", &band2); //second band
	
	printf("Please enter the multiplier band: \n");
	scanf(" %c", &band_m); //multiplier band
	
	printf("Please enter the tolerance band: \n");
	scanf(" %c", &band_t); //tolerance band
	
	
	
	//Printing a part of result sentence to user
	printf("Resistor bands: ");
	
	
	
	//Deciding the first band
	if(band1== 107 || band1==75){
		b1=0;
		printf("Black ");
	}
	else if(band1==98 || band1== 66){
		b1=1;
		printf("Brown ");
	}
	else if(band1== 114 || band1== 82){
		b1=2;
		printf("Red ");
	}
	else if(band1== 111 || band1== 79){
		b1=3;
		printf("Orange ");
	}
	else if(band1== 101 || band1== 69){
		b1=4;
		printf("Yelllow ");
	}
	else if(band1== 103 || band1== 71){
		b1=5;
		printf("Green ");
	}
	else if(band1== 117 || band1== 85){
		b1=6;
		printf("Blue ");
	}
	else if(band1== 118|| band1== 86){
		b1=7;
		printf("Violet ");
	}
	else if(band1== 121|| band1== 89){
		b1=8;
		printf("Grey ");
	}
	else if(band1== 119|| band1== 87){
		b1=9;
		printf("White ");
	}
	
	
	
	//Deciding the second band
	if(band2== 107 || band2==75){
		b2=0;
		printf("Black ");
	}
	else if(band2==98 || band2== 66){
		b2=1;
		printf("Brown ");
	}
	else if(band2== 114 || band2== 82){
		b2=2;
		printf("Red ");
	}
	else if(band2== 111 || band2== 79){
		b2=3;
		printf("Orange ");
	}
	else if(band2== 101 || band2== 69){
		b2=4;
		printf("Yellow ");
	}
	else if(band2== 103 || band2== 71){
		b2=5;
		printf("Green ");
	}
	else if(band2== 117 || band2== 85){
		b2=6;
		printf("Blue ");
	}
	else if(band2== 118|| band2== 86){
		b2=7;
		printf("Violet ");
	}
	else if(band2== 121|| band2== 89){
		b2=8;
		printf("Grey ");
	}
	else if(band2== 119|| band2== 87){
		b2=9;
		printf("White ");
	}
	
	
	
	/*Deciding the multiplier band*/
	if(band_m== 107 || band_m==75){
		b_m=1;
		printf("Black ");
	}
	else if(band_m==98 || band_m== 66){
		b_m=10;
		printf("Brown ");
	}
	else if(band_m== 114 || band_m== 82){
		b_m=100;
		printf("Red ");
	}
	else if(band_m== 111 || band_m== 79){
		b_m=1000;
		printf("Orange ");
	}
	else if(band_m== 101 || band_m== 69){
		b_m=10000;
		printf("Yellow ");
	}
	else if(band_m== 103 || band_m== 71){
		b_m=100000;
		printf("Green ");
	}
	else if(band_m== 117 || band_m== 85){
		b_m=1000000;
		printf("Blue ");
	}
	else if(band_m== 118|| band_m== 86){
		b_m=10000000;
		printf("Violet ");
	}
	else if(band_m== 108|| band_m== 76){
		b_m=0.1;
		printf("gold ");
	}
	else if(band_m== 115|| band_m== 83){
		b_m=0.01;
		printf("Silver ");
	}



	/*Deciding the tolerance band*/
	if(band_t==98 || band_t== 66){
		b_t=1;
		printf("Brown ");
	}
	else if(band_t== 114 || band_t== 82){
		b_t=2;
		printf("Red ");
	}
	else if(band_t== 103 || band_t== 71){
		b_t=0.5;
		printf("Green ");
	}
	else if(band_t== 117 || band_t== 85){
		b_t=0.25;
		printf("Blue ");
	}
	else if(band_t== 118|| band_t== 86){
		b_t=0.10;
		printf("Violet ");
	}
	else if(band_t== 121|| band_t== 89){
		b_t=0.05;
		printf("Grey ");
	}
	else if(band_t== 108|| band_t== 76){
		b_t=5;
		printf("Gold ");
	}
	else if(band_t== 115|| band_t== 83){
		b_t=10;
		printf("Silver ");
	}
	
	
	
	twoDigit=b1*10+b2; //variable for calculation
	resistance=twoDigit*b_m; //resistance calculation
	
	
	
	printf("Resistance: "); //A part of output sentence
	
	
	
	/*Deciding a unit of resistance and
	   printing an appropriate unit & tolerance*/
	if(resistance>999 && resistance<1000000)
	{
		resistanceForPrint=resistance/1000;
		printf("%.2lf KOhms +/- %.2lf%%\n", resistanceForPrint, b_t);
	}
	else if(resistance>999999)
	{
		resistanceForPrint=resistance/1000000;
		printf("%.2lf MOhms +/- %.2lf%%\n", resistanceForPrint, b_t);
	}
	else
		printf("%.2lf Ohms +/- %.2lf%%\n", resistance, b_t);
		
		
    return 0;
}
