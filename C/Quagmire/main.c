/***********************************************************************
* main.c
* The core main program. Note minor changes for the new code.
***********************************************************************/
/* Include any libraries needed. */
#include <stdio.h>
/* Also include the work header. */
#include "Quagmire.h"

/* Allow the programs to function in a batch or script environment. */
int main(int argc, char *argv[]){
/* Declare the few variables needed. */
	int errcode;
	FILE *fi,*fo,*fk;

/* Error check argc and display usage instructions. */
	if(argc<ARGLMTL||argc>ARGLMTU){
		UsageQuagmire();
		/* Return with an error exit. */
		return 1;
	}
/* Open files as needed and trap errors. */
	if((fk=fopen(argv[2],"rt"))==NULL){
		printf("Can't open key file '%s'\n",argv[2]);
		return 1;
	}
	if((fi=fopen(argv[3],"rt"))==NULL){
		printf("Can't open input file '%s'\n",argv[3]);
		fclose(fi);
		return 1;
	}
	if((fo=fopen(argv[4],"wt"))==NULL){
		printf("Can't open output file '%s'\n",argv[4]);
		fclose(fi);
		return 1;
	}
/* Initialize the work function. Set key and files. */
	if((errcode=InitQuagmire(fi,fo,argv[1][0]))!=0){
		/* Init failed */
		return errcode;
	}
	/* Set key array. */
	if((errcode=SetKeyQuagmire(fk))!=0){
		/* Main failed */
		printf("Key file read failed %d\n",errcode);
		return errcode;
	}
	fclose(fk);
/* Call the work function. */
	if((errcode=MainQuagmire())!=0){
		/* Main failed */
		return errcode;
	}
/* Clean up things after work is done. */
	if((errcode=DoneQuagmire())!=0){
		/* Done failed */
		return errcode;
	}
/* Close files that were opened. */
	fclose(fi);
	fclose(fo);
/* Exit no error */
	return 0;
}
