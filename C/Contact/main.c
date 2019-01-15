/***********************************************************************
* main.c
* The core main program.
***********************************************************************/
/* Include any libraries needed. */
#include <stdio.h>
/* Also include the Contact header. */
#include "Contact.h"

/* Allow the programs to function in a batch or script environment. */
int main(int argc, char *argv[]){
/* Declare the few variables needed. */
	int errcode;
	FILE *fi,*fo;

/* Error check argc and display usage instructions. */
	if(argc<ARGLMTL||argc>ARGLMTU){
		UsageContact();
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
/* Initialize the Contact function. */
	if((errcode=InitContact(fi,fo))!=0){
		/* Init failed */
		return errcode;
	}
/* Call the Contact function. */
	if((errcode=MainContact())!=0){
		/* Main failed */
		return errcode;
	}
/* Clean up things after Contact is done. */
	if((errcode=DoneContact())!=0){
		/* Done failed */
		return errcode;
	}
/* Close files that were opened. */
	fclose(fi);
	fclose(fo);
/* Exit no error */
	return 0;
}
