/**************************************************************************
* Case.c
**************************************************************************/
#include <stdio.h>

#include "Case.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int dir;

int InitCase(FILE *fi, FILE *fo, int d){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	if(d=='U'||d=='u'){
		dir=1;
	}else{
		dir=0;
	}
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainCase(void){
	int c;
	while((c=fgetc(fin))!=EOF){
		/* Change Upper to lower case. */
		if(c>='a'&&c<='z'&&dir==1){
			c-=32;
		}
		if(c>='A'&&c<='Z'&&dir==0){
			c+=32;
		}
		fputc(c,fout);
	}
	return ErrorFlag;
}
int DoneCase(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsageCase(void){
	printf(" usage: Case c infile outfile\n");
	printf(" c = U or L for coversion to Upper or Lower case.\n");
	printf(" infile  = input path and filename.\n");
	printf(" outfile = output path and file name.\n");
}
