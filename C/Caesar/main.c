/***********************************************************************
* main.c
* The core main program. Note minor changes for the new code.
***********************************************************************/
/* Include any libraries needed. */
#include <stdio.h>
/* Also include the work header. */
#include "caesar.h"

/* Allow the programs to function in a batch or script environment. */
int main(int argc, char *argv[]){
/* Declare the few variables needed. */
	int errcode;
	FILE *fi,*fo;

/* Error check argc and display usage instructions. */
	if(argc<ARGLMTL||argc>ARGLMTU){
		UsageWork();
		/* Return with an error exit. */
		return 1;
	}
/* Open files as needed and trap errors. */
	if((fi=fopen(argv[2],"rt"))==NULL){
		printf("Can't open input file '%s'\n",argv[1]);
		return 1;
	}
	if((fo=fopen(argv[3],"wt"))==NULL){
		printf("Can't open output file '%s'\n",argv[2]);
		fclose(fi);
		return 1;
	}
/* Initialize the work function. Set key and files. */
	if((errcode=InitWork(fi,fo,argv[1][0],argv[1][1]))!=0){
		/* Init failed */
		return errcode;
	}
/* Call the work function. */
	if((errcode=MainWork())!=0){
		/* Main failed */
		return errcode;
	}
/* Clean up things after work is done. */
	if((errcode=DoneWork())!=0){
		/* Done failed */
		return errcode;
	}
/* Close files that were opened. */
	fclose(fi);
	fclose(fo);
/* Exit no error */
	return 0;
}
