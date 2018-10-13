/**************************************************************************
* work.c
* A placeholder for future projects
**************************************************************************/
#include <stdio.h>

#include "FreqCnt.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;

/* These variables need to be at least 32 bit. */
unsigned long fc[26];
unsigned long tc;
unsigned long lc;
int srt[26];

int InitFreqCnt(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainFreqCnt(void){
	int c,f,x;
	/* Read and count */
	while((c=fgetc(fin))!=EOF){
		/* Count total file length. */
		tc++;
		/* Fix lower to upper case */
		if(c>='a'&&c<='z')c-=32;
		/* Count letters and total letters. */
		if(c>='A'&&c<='Z'){
			x=c-65;
			fc[x]++;
			lc++;
		}
	}
	/* Init sort array. */
	for(x=0;x<26;x++)srt[x]=x;
	/* Simple sort by frequency. */
	do{
		f=0;
		for(x=0;x<25;x++){
			if(fc[srt[x+1]]>fc[srt[x]]){
				c=srt[x];
				srt[x]=srt[x+1];
				srt[x+1]=c;
				f=1;
			}
		}
		/* Loop until no swaps. */
	}while(f!=0);
	return ErrorFlag;
}
int DoneFreqCnt(void){
	int x;
	/* Print the frequencies and counts. */
	for(x=0;x<26;x++){
		fprintf(fout,"%10d  %c     %c  %10d\n",fc[x],x+65,srt[x]+65,fc[srt[x]]);
	}
	fprintf(fout,"\nTotal letter count = %d\n",lc);
	fprintf(fout,"File byte count = %d\n",tc);
	return ErrorFlag;
}
void UsageFreqCnt(void){
	printf(" Usage: freqcnt infile outfile\n");
	printf(" Program expects ASCII text input.");
}
