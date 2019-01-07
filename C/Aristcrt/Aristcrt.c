/**************************************************************************
* aristcrt.c
* The aristocrat cipher (General letter substitution)
**************************************************************************/
#include <stdio.h>

#include "aristcrt.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int shft;
int dir;
char key[27][2];

int InitAristcrt(FILE *fi, FILE *fo, int d){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Set encrypt or decrypt mode. */
	if(d=='E'||d=='e'){
		dir=0;
	}else{
		dir=1;
	}
	/* Nothing else needed here */
	return ErrorFlag;
}
int SetKeyAristcrt(FILE *kf){
	int ac[27];
	int c,kc=0,x;
	char tk[28];
	
	ErrorFlag=0;
	/* Read the key file. */
	while((c=fgetc(kf))!=EOF&&kc<27){
		/* Fix lower case letters. Ignore all else. */
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			c-=65;
			tk[kc]=(char)c;
			kc++;
		}
	}
	/* Return Error if count check fails. */
	if(kc>26){
		ErrorFlag=1;
		return 1;
	}
	/* Process key and check that it's valid. */
	for(x=0;x<26;x++)ac[x]=0;
	/* Count letters and copy key. */
	for(x=0;x<26;x++){
		ac[tk[x]]++;
		key[x][0]=tk[x];
	}
	/* Valid keys will only have one of each letter. */
	for(x=0;x<26;x++){
		if(ac[x]!=1){
			ErrorFlag=1;
			return 1;
		}
		/* Make decrypt key. */
		key[key[x][0]][1]=x;
	}
	return 0;
}
int MainAristcrt(void){
	int c,x;
	/* A simple version of the Caesar cipher */
	while((c=fgetc(fin))!=EOF){
		x=c;
		/* Perform rot on lower case only. */
		if(c>='a'&&c<='z'){
			c=key[x-97][dir]+97;
		}
		/* Perform rot on upper case only. */
		if(c>='A'&&c<='Z'){
			c=key[x-65][dir]+65;
		}
		/* leave everything else intact. */
		fputc(c,fout);
	}
	return ErrorFlag;
}
int DoneAristcrt(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsageAristcrt(void){
	printf(" usage: aristcrt M keyfile infile outfile\n");
	printf(" M (mode)= E (encrypt) or D (decrypt) mode\n");
	printf(" keyfile = 26 letter mixed alphabet key file\n");
	printf(" infile  = input file\n");
	printf(" outfile = output file\n");
	printf(" Encrypt = caesar E key.txt ptxt.txt ctxt.txt\n");
	printf(" Decrypt = caesar D key.txt ptxt.txt ctxt.txt\n");
}
