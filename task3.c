#include "1436508610_103__compact_coeff.h"
#include "1436508628_101__compact_R.h"
#include <stdio.h>

int Timing_Synchronization(int *Samples,int *Coeff);
int modulo=0;


const int DetThr=0x69000;
int mod_out;
int i,j,sample[256];
int main()
{  
 for(j=0;j<256;j++) sample[j]=0; // intialization, not necessary on a simulator, may be needed on a board// Parsing one by one all input samples. Every time we add a sample in slot 1, // we shift all samples of one unit and we remove the sample in slot 256, then we run the FIR again
 for(i=0;i<3394;i++) { 
  for(j=255;j>0;j--) sample[j]=sample[j-1];sample[0]=R[i];
mod_out=Timing_Synchronization(sample,coef); 
	 
     if (mod_out>=DetThr)
        {
  // BOOOOOOOONG!!!!! Synchronization Achieved!!!	// Hint -> Place a Breakpoint here for performance measurements!
               return(i);  //whenever the peak is found the system quits.               // (in the simulation data the peak is located at i=715)
        };
     }
}

int Timing_Synchronization(int *Samples,int *Coeff) 
{
	int k;
	//int n=255;
	
	int re1=0;	//real part of the first vector
	int im1=0;  //imaginary part of the first vector	
	int im2=0;
	int re2=0;
	
	int accRe=0;//accumalated real 
	int accIm=0;//accumalated imaginary
	
	for (k=0; k<256; k++)
	{
		re1=(Samples[k]>>16);//get top 16 bits
		im1=((Samples[k]<<16)>>16); //get lower 16
		
		re2=(Coeff[k]>>16);//get top 16 bits
		im2=((Coeff[k]<<16)>>16); 

		accRe+= ((re1*re2)>>16)-((im1*im2)>>16);
		accIm+= ((re1*im2)>>16)+((re2*im1)>>16);
	}
	modulo=(accRe*accRe)+(accIm*accIm);

	return modulo;
}
