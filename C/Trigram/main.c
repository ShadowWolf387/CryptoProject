/***********************************************************************
* main.c
* The core main program.
***********************************************************************/
/* Include any libraries needed. */
#include <stdio.h>
/* Also include the Trigram header. */
#include "Trigram.h"

/* Allow the programs to function in a batch or script environment. */
int main(int argc, char *argv[]){
/* Declare the few variables needed. */
	int errcode;
	FILE *fi,*fo;

/* Error check argc and display usage instructions. */
	if(argc<ARGLMTL||argc>ARGLMTU){
		UsageTrigram();
		/* Return with an error exit. */
		return 1;
	}
/* Open files as needed and trap errors. */
	if((fi=fopen(argv[1],"rt"))==NULL){
		printf("Can't open input file '%s'\n",argv[1]);
		return 1;
	}
	if((fo=fopen(argv[2],"wt"))==NULL){
		printf("Can't open output file '%s'\n",argv[2]);
		fclose(fi);
		return 1;
	}
/* Initialize the Trigram function. */
	if((errcode=InitTrigram(fi,fo))!=0){
		/* Init failed */
		return errcode;
	}
/* Call the Trigram function. */
	if((errcode=MainTrigram())!=0){
		/* Main failed */
		return errcode;
	}
/* Clean up things after Trigram is done. */
	if((errcode=DoneTrigram())!=0){
		/* Done failed */
		return errcode;
	}
/* Close files that were opened. */
	fclose(fi);
	fclose(fo);
/* Exit no error */
	return 0;
}
