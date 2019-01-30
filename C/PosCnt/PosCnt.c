/**************************************************************************
* PosCnt.c
* Position frequency counter
* Run time should be about double the standard freqcnt.
**************************************************************************/
#include <stdio.h>
#include "PosCnt.h"

#define WORDLMT 20
#define WORDBUF WORDLMT + 5 /* Allows for long words not counted. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;

/* These variables need to be at least 32 bit. */
unsigned long pc[WORDLMT][WORDLMT][26];
unsigned long tc;
unsigned long lc;
unsigned long wlc[WORDLMT]; /* Word length count */

int InitPosCnt(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainPosCnt(void){
	int word[WORDBUF];
	int c,f,w=0,x,y;
	/* Read and count */
	while((c=fgetc(fin))!=EOF){
		/* Count total file length. Just a little sanity check. */
		tc++;
		/* Fix lower to upper case */
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			/* Build a word */
			word[w]=c-65;
			/* Prevent buffer overrun. */
			if(w<WORDBUF-1)w++;
		}else{
			/* Not a letter. */
			/* Terminate and count a word. Count contractions. */
			if(w>0&&w<=WORDLMT&&c!=39){
				word[w]=0; /* May not be needed. */
				y=w-1;
				wlc[y]++;
				/* Array format: pc[size-1][position-1][freqcnt] */
				for(x=0;x<w;x++){
					/* Count position frequency */
					pc[y][x][word[x]]++;
					/* For stats, only count letters in counted words. */
					lc++;
				}
				w=0;
			}else{
				/* Word was oversized, skipping white space or saving a contraction. */
				if(c!=39)w=0;
			}
		}
	}
	return ErrorFlag;
}
int DonePosCnt(void){
	int x,y,z,wc=0,lfc;
	/* Print the frequencies and counts. */
	for(x=0;x<26;x++){
		lfc=0;
		/* save letters */
		fprintf(fout," %c",x+65);
		for(z=0;z<WORDLMT;z++)fprintf(fout," %9d",z+1);
		for(y=0;y<WORDLMT;y++){
			fprintf(fout,"\n%2d",y+1);
			for(z=0;z<=y;z++){
				fprintf(fout," %9d",pc[y][z][x]);
				lfc+=pc[y][z][x];
			}
		}
		fprintf(fout,"\nLetter Frequency Count = %d\n\n",lfc);
	}
	fprintf(fout,"Word Length  Counts\n");
	for(x=0;x<WORDLMT;x++){
		fprintf(fout,"%2d  %9d\n",x+1,wlc[x]);
		wc+=wlc[x];
	}
	fprintf(fout,"\nTotal Word Count = %d\n",wc);
	fprintf(fout,"Total Letter Count = %d\n",lc);
	fprintf(fout,"File Byte Count = %d\n",tc);
	return ErrorFlag;
}
void UsagePosCnt(void){
	printf(" Usage: PosCnt infile outfile\n");
	printf(" Program expects ASCII text input.");
}
