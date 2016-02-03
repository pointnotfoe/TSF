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
