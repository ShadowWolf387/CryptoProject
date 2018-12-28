/**************************************************************************
* caesar.c
* The caesar cipher
**************************************************************************/
#include <stdio.h>

#include "caesar.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int shft;
int dir;

int InitWork(FILE *fi, FILE *fo,int s, int d){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* convert the key to 0-26 */
	if(s>='a'&&s<='z')s-=32;
	if(s>='A'&&s<='Z'){
		shft=s-65;
	}else{
		ErrorFlag=1;
	}
	/* Set encrypt or decrypt mode. */
	if(d=='E'||d=='e'){
		dir=1;
	}else{
		dir=-1;
	}
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainWork(void){
	int c;
	/* A simple version of the Caesar cipher */
	while((c=fgetc(fin))!=EOF){
		/* Perform rot on lower case only. */
		if(c>='a'&&c<='z'){
			c+=(shft*dir);
			if(c>'z')c-=26;
			if(c<'a')c+=26;
		}
		/* Perform rot on upper case only. */
		if(c>='A'&&c<='Z'){
			c+=(shft*dir);
			if(c>'Z')c-=26;
			if(c<'A')c+=26;
		}
		/* leave everything else intact. */
		fputc(c,fout);
	}
	return ErrorFlag;
}
int DoneWork(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsageWork(void){
	printf(" usage: caesar KM infile outfile\n");
	printf("   K = A-Z key\n");
	printf("   M = E (encrypt) or D (decrypt)");
	printf(" Encrypt = caesar CE ptxt.txt ctxt.txt");
	printf(" Decrypt = caesar CD ctxt.txt ptxt.txt");
}
