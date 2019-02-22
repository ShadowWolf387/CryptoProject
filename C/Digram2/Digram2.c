/**************************************************************************
* Digram.c
* 
**************************************************************************/
#include <stdio.h>

#include "Digram2.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int dgrm[26][26];
int lc,dc;

int InitDigram2(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainDigram2(void){
	int c,c1,c2,dl,x,y;
	/* Digram counter */
	lc=dc=dl=0;
	for(x=0;x<26;x++){
		for(y=0;y<26;y++)dgrm[x][y]=0;
	}
	while((c=fgetc(fin))!=EOF){
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			c1=c2;
			c2=c-65;
			lc++;
			dl++;
			if(dl<2)continue;
			dgrm[c1][c2]++;
			dl=0;
			dc++;
		}
	}
	return ErrorFlag;
}
int DoneDigram2(void){
	int x,y,z;
	int sets[]={0,7,14,21,26};
	/* Write digram table(s). */
	/* Write table alphabet top row. */
	for(z=1;z<5;z++){
		fprintf(fout,"   ");
		for(y=sets[z-1];y<sets[z];y++)fprintf(fout,"    %c    ",y+65);
		fprintf(fout,"\n");
		for(x=0;x<26;x++){
			fprintf(fout,"%c",x+65);
			for(y=sets[z-1];y<sets[z];y++){
				fprintf(fout," %8d",dgrm[x][y]);
			}
			fprintf(fout,"\n");
		}
		fprintf(fout,"\n\n");
	}
	fprintf(fout,"Letter Count = %d\n",lc);
	fprintf(fout,"Digram Count = %d\n",dc);
return ErrorFlag;
}
void UsageDigram2(void){
	printf(" usage: Digram2 infile outfile\n\n");
	printf(" Counts letter pairs ignoring word divisions.\n");
	printf(" Strictly counts letter pairs only once. If the text is\n");
	printf(" 'COUNT PAIRS' CO, UN, TP, AI, RS, would each be counted.\n");
}
