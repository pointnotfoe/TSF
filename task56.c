#include "1436508610_103__compact_coeff.h"
//#include "1436508628_101__compact_R.h"

#define LED				(int*)0x41210000
#define SWITCH  		(int*)0x41220000
#define BUTTON 			(int*) 0x41200000
#define LED_CONTROL 	(int*)(LED+4)
#define SWITCH_CONTROL  (int*)(SWITCH+4)
#define BUTTON_CONTROL  (int*)(BUTTON+4)


float Timing_Synchronization_float(int *Samples,int *Coeff);
float Timing_Synchronization_int(int *Samples,int *Coeff);
float Timing_Synchronization_inline(int *Samples,int *Coeff);



const float DetThr_f=1e+15;
const int DetThr=0x69000;

float mod_out_f;
int mod_out;
int i,j,sample[40000],SYNCH[20];

int main(void)
{
	int a;//read write status 
	int delay;
	int zero;//for SYNCH counter
	int buttonx; // button value
	int j_alt;//alternate value of j in case of button 1 pressed
	
	*LED_CONTROL=0x0;//LEDs as output
	*SWITCH_CONTROL=0xff; //SWITCHes as input
	*BUTTON_CONTROL=0xff;//setting BUTTONS as inputs
	
	
	while(1)
	{
		buttonx=*BUTTON; 
		if(buttonx==0x1)//if button 1 is pressed
		{
			j_alt=10000;
		}
		else if(buttonx==0x0)//if button 0 is pressed
		{
			j_alt=40000;
		}
		
		{  
 for(j=0;j<j_alt;j++) sample[j]=0; // intialization, not necessary on a simulator, may be needed on a board// Parsing one by one all input samples. Every time we add a sample in slot 1, // we shift all samples of one unit and we remove the sample in slot 256, then we run the FIR again
 for(i=0;i<3394;i++) { 
  for(j=(j_alt-1);j>0;j--) sample[j]=sample[j-1];sample[0]=RAND(1)>>8;//random array
  
	 a=*SWITCH;//checking every loop if another switch has been pressed
		if(a==0x41220000)//switch zero is pressed (if not then a==0x0)
		{
			mod_out_f=Timing_Synchronization_float(sample,coef); 
			
			if(buttonx==0x1)
		{
			DetThr_f=DetThr_f*.9;
		}
		else if(buttonx==0x0)//if button 0 is pressed
		{
			for(zero=0;zero<20;zero++)
			{SYNCH[zero]=sample[zero];}
		}
		
			    if (mod_out_f>=DetThr_f)
        {
			for(delay=0; delay<715; delay++)//delay
			{
				
			}
			*LED=a;
  // BOOOOOOOONG!!!!! Synchronization Achieved!!!	// Hint -> Place a Breakpoint here for performance measurements!
               return(i);  //whenever the peak is found the system quits.               // (in the simulation data the peak is located at i=715)
        };
		}
		else if(a==0x41220001)//switch 1 is pressed (if not then a==0x1)
		{
			mod_out=Timing_Synchronization_int(sample,coef); 
			if(buttonx==0x1)
		{
			DetThr=DetThr*.9;
		}
		else if(buttonx==0x0)//if button 0 is pressed
		{
			for(zero=0;zero<20;zero++)
			{SYNCH[zero]=sample[zero];}
		}
		
			    if (mod_out>=DetThr)
        {
			for(delay=0; delay<715; delay++)
			{
				
			}
			*LED=a;
  // BOOOOOOOONG!!!!! Synchronization Achieved!!!	// Hint -> Place a Breakpoint here for performance measurements!
               return(i);  //whenever the peak is found the system quits.               // (in the simulation data the peak is located at i=715)
        };
		}
		else if(a==0x41220002)//switch 2 is pressed(if not then a==0x2)
		{
			mod_out=Timing_Synchronization_inline(sample,coef); 
				if(buttonx==0x1)
		{
			DetThr=DetThr*.9;
		}
		else if(buttonx==0x0)//if button 0 is pressed
		{
			for(zero=0;zero<20;zero++)
			{SYNCH[zero]=sample[zero];}
		}
			   if (mod_out>=DetThr)
        {
			for(delay=0; delay<715; delay++)
			{
				
			}
			*LED=a;
  // BOOOOOOOONG!!!!! Synchronization Achieved!!!	// Hint -> Place a Breakpoint here for performance measurements!
               return(i);  //whenever the peak is found the system quits.               // (in the simulation data the peak is located at i=715)
        };
		}
		
		
    
     }
}

		
		
	}
	
}

int Timing_Synchronization_inline(int *Samples,int *Coeff) 
{
	int modulo=0;

	int i=4;
	int shift;
	int a=0;
	int b=0;
	int Rcoeff;
	int Icoeff;
	int Rproduct;
	int Ma;
	int Mb;
	int Atotal=0;
	int Btotal=0;
	int Rsample;
	int Isample;
	int count=0;

__asm { 
	Loop:
				LDR Rsample,[Samples,count,LSL #2]
				MOV Rsample,Rsample,ASR 16
	
				LDR Isample,[Samples,count,LSL #2]
				MOV Isample, Isample,LSL 16
				MOV Isample, Isample, ASR 16
	
				LDR Rcoeff,[Coeff,count, LSL #2]
				MOV Rcoeff,Rcoeff,ASR 16
	
				LDR Icoeff,[Coeff,count, LSL#2]
				MOV Icoeff, Icoeff,LSL 16
				MOV Icoeff, Icoeff, ASR 16
				
				MUL Ma,Isample,Icoeff
				MOV Ma,Ma,ASR 16
				MUL Mb,Isample,Rcoeff
				MOV Mb,Mb,ASR 16
				MUL a,Rsample,Rcoeff
				MUL	b,Rsample,Icoeff
				MOV b,b,ASR 16
				MOV a,a,ASR 16
				SUB a,a,Ma
				ADD	b,b,Mb
				ADD Atotal,Atotal,a
				ADD Btotal, Btotal,b
				CMP count,256
				ADD count,count,1
				BNE Loop			
				MUL Mb,Btotal,Btotal
				MLA	modulo,Atotal,Atotal,Mb};
		return modulo;
}

int Timing_Synchronization_int(int *Samples,int *Coeff) 
{
	int k;
	int modulo=0;

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

float Timing_Synchronization_float(int *Samples,int *Coeff) 
{
	float modulo=0;

	int k;
	//int n=255;
	
	float re1=0;	//real part of the first vector
	float im1=0;  //imaginary part of the first vector	
	float im2=0;
	float re2=0;
	
	float accRe=0;//accumalated real 
	float accIm=0;//accumalated imaginary
	
	for (k=0; k<256; k++)
	{
		re1=(float)(Samples[k]>>16);//get top 16 bits
		im1=(float)((Samples[k]<<16)>>16); //get lower 16
		
		re2=(float)(Coeff[k]>>16);//get top 16 bits
		im2=(float)((Coeff[k]<<16)>>16); 

		accRe+= (re1*re2)- (im1*im2);
		accIm+=(re1*im2)+(re2*im1);
	}
	modulo=(accRe*accRe)+(accIm*accIm);

	return modulo;
}
