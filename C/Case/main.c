/***********************************************************************
* main.c
***********************************************************************/
/* Include any libraries needed. */
#include <stdio.h>
/* Also include the Case header. */
#include "Case.h"

/* Allow the programs to function in a batch or script environment. */
int main(int argc, char *argv[]){
/* Declare the few variables needed. */
	int errcode;
	FILE *fi,*fo;

/* Error check argc and display usage instructions. */
	if(argc<ARGLMTL||argc>ARGLMTU){
		UsageCase();
		/* Return with an error exit. */
		return 1;
	}
/* Open files as needed and trap errors. */
	if((fi=fopen(argv[2],"rt"))==NULL){
		printf("Can't open input file '%s'\n",argv[2]);
		return 1;
	}
	if((fo=fopen(argv[3],"wt"))==NULL){
		printf("Can't open output file '%s'\n",argv[3]);
		fclose(fi);
		return 1;
	}
/* Initialize the Case function. */
	if((errcode=InitCase(fi,fo,argv[1][0]))!=0){
		/* Init failed */
		return errcode;
	}
/* Call the Case function. */
	if((errcode=MainCase())!=0){
		/* Main failed */
		return errcode;
	}
/* Clean up things after Case is done. */
	if((errcode=DoneCase())!=0){
		/* Done failed */
		return errcode;
	}
/* Close files that were opened. */
	fclose(fi);
	fclose(fo);
/* Exit no error */
	return 0;
}
