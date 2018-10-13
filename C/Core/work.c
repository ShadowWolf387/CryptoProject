/**************************************************************************
* work.c
* A placeholder for future projects
**************************************************************************/
#include <stdio.h>

#include "work.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;

int InitWork(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainWork(void){
	int c;
	/* A simple version of Rot13 */
	while((c=fgetc(fin))!=EOF){
		/* Perform rot13 on lower case only. */
		if(c>='a'&&c<='z'){
			c+=13;
			if(c>'z')c-=26;
		}
		/* Perform rot13 on upper case only. */
		if(c>='A'&&c<='Z'){
			c+=13;
			if(c>'Z')c-=26;
		}
		fputc(c,fout);
	}
	return ErrorFlag;
}
int DoneWork(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsageWork(void){
	printf(" usage: work <infile> <outfile>\n");
}
