/**************************************************************************
* Trigram.c
* 
**************************************************************************/
#include <stdio.h>

#include "Trigram.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int tgrm[26][26][26];
int lc;

int InitTrigram(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainTrigram(void){
	int c,c1,c2,c3,x,y,z;
	/* Trigram counter */
	lc=0;
	for(x=0;x<26;x++){
		for(y=0;y<26;y++){
			for(z=0;z<26;z++)tgrm[x][y][z]=0;
		}
	}
	while((c=fgetc(fin))!=EOF){
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			c1=c2;
			c2=c3;
			c3=c-65;
			lc++;
			if(lc<3)continue;
			tgrm[c1][c2][c3]++;
		}
	}
	return ErrorFlag;
}
int DoneTrigram(void){
	int x,y,z;
 	/* Write Trigram table(s). */
 	/* No good way to do a table so there are 26 digram tables. */
 	for(z=0;z<26;z++){
		/* Write table alphabet top row. */
		fprintf(fout,"(%c)",z+65);
		for(y=0;y<7;y++)fprintf(fout,"    %c    ",y+65);
		fprintf(fout,"\n");
		for(x=0;x<26;x++){
			fprintf(fout,"%c",x+65);
			for(y=0;y<7;y++){
				fprintf(fout," %8d",tgrm[z][x][y]);
			}
			fprintf(fout,"\n");
		}
		fprintf(fout,"\n\n   ");
		for(y=7;y<14;y++)fprintf(fout,"    %c    ",y+65);
		fprintf(fout,"\n");
		for(x=0;x<26;x++){
			fprintf(fout,"%c",x+65);
			for(y=7;y<14;y++){
				fprintf(fout," %8d",tgrm[z][x][y]);
			}
			fprintf(fout,"\n");
		}
		fprintf(fout,"\n\n   ");
		for(y=14;y<21;y++)fprintf(fout,"    %c    ",y+65);
		fprintf(fout,"\n");
		for(x=0;x<26;x++){
			fprintf(fout,"%c",x+65);
			for(y=14;y<21;y++){
				fprintf(fout," %8d",tgrm[z][x][y]);
			}
			fprintf(fout,"\n");
		}
		fprintf(fout,"\n\n   ");
		for(y=21;y<26;y++)fprintf(fout,"    %c    ",y+65);
		fprintf(fout,"\n");
		for(x=0;x<26;x++){
			fprintf(fout,"%c",x+65);
			for(y=21;y<26;y++){
				fprintf(fout," %8d",tgrm[z][x][y]);
			}
			fprintf(fout,"\n");
		}
		fprintf(fout,"\n\n");
	}
	fprintf(fout,"\nLetter Count = %d\n",lc);
return ErrorFlag;
}
void UsageTrigram(void){
	printf(" usage: Trigram infile outfile\n");
	printf(" Counts letter triples ignoring word divisions.\n");
	printf(" Writes 26 digram tables using this format...\n");
	printf(" T1 = corner, T2 = row, T3 = column\n");
}
