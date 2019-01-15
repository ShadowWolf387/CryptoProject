/**************************************************************************
* Digram.c
* 
**************************************************************************/
#include <stdio.h>

#include "Digram.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int dgrm[26][26];
int lc;

int InitDigram(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainDigram(void){
	int c,c1,c2,x,y;
	/* Digram counter */
	lc=0;
	for(x=0;x<26;x++){
		for(y=0;y<26;y++)dgrm[x][y]=0;
	}
	while((c=fgetc(fin))!=EOF){
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			c1=c2;
			c2=c-65;
			lc++;
			if(lc<2)continue;
			dgrm[c1][c2]++;
		}
	}
	return ErrorFlag;
}
int DoneDigram(void){
	int x,y;
	/* Write digram table(s). */
	/* Write table alphabet top row. */
	fprintf(fout,"   ");
	for(y=0;y<7;y++)fprintf(fout,"    %c    ",y+65);
	fprintf(fout,"\n");
	for(x=0;x<26;x++){
		fprintf(fout,"%c",x+65);
		for(y=0;y<7;y++){
			fprintf(fout," %8d",dgrm[x][y]);
		}
		fprintf(fout,"\n");
	}
	fprintf(fout,"\n\n   ");
	for(y=7;y<14;y++)fprintf(fout,"    %c    ",y+65);
	fprintf(fout,"\n");
	for(x=0;x<26;x++){
		fprintf(fout,"%c",x+65);
		for(y=7;y<14;y++){
			fprintf(fout," %8d",dgrm[x][y]);
		}
		fprintf(fout,"\n");
	}
	fprintf(fout,"\n\n   ");
	for(y=14;y<21;y++)fprintf(fout,"    %c    ",y+65);
	fprintf(fout,"\n");
	for(x=0;x<26;x++){
		fprintf(fout,"%c",x+65);
		for(y=14;y<21;y++){
			fprintf(fout," %8d",dgrm[x][y]);
		}
		fprintf(fout,"\n");
	}
	fprintf(fout,"\n\n   ");
	for(y=21;y<26;y++)fprintf(fout,"    %c    ",y+65);
	fprintf(fout,"\n");
	for(x=0;x<26;x++){
		fprintf(fout,"%c",x+65);
		for(y=21;y<26;y++){
			fprintf(fout," %8d",dgrm[x][y]);
		}
		fprintf(fout,"\n");
	}
	fprintf(fout,"\n\nLetter Count = %d\n",lc);
return ErrorFlag;
}
void UsageDigram(void){
	printf(" usage: Digram infile outfile\n");
	printf("Counts letter pairs ignoring word divisions.\n");
}
