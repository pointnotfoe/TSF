#include "1436508610_103__compact_coeff.h"
#include "1436508628_101__compact_R.h"
#include <stdio.h>

float Timing_Synchronization(int *Samples,int *Coeff);
float modulo=0;
float modulo1=0;

int main()
{
		modulo1=Timing_Synchronization(R,coef);
} 
float Timing_Synchronization(int *Samples,int *Coeff) 
{
	int j;
	int n=255;
	
	float re1=0;	//real part of the first vector
	float im1=0;  //imaginary part of the first vector	
	float im2=0;
	float re2=0;
	
	float accRe=0;//accumalated real 
	float accIm=0;//accumalated imaginary
	
	for (j=0; j<256; j++)
	{
		re1=(float)(Samples[j]>>16);//get top 16 bits
		im1=(float)((Samples[j]<<16)>>16); //get lower 16
		
		re2=(float)(Coeff[j]>>16);//get top 16 bits
		im2=(float)((Coeff[j]<<16)>>16); 

		accRe+= (re1*re2)- (im1*im2);
		accIm+=(re1*im2)+(re2*im1);
	}
	modulo=(accRe*accRe)+(accIm*accIm);

	return modulo;
}
