/**************************************************************************
* Polybius.c
* The Polybius cipher (5x5 square substitution)
* Modified 25 letter substitution table. "J" is removed.
**************************************************************************/
#include <stdio.h>

#include "Polybius.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int shft;
int dir;
char key[27][2];

int InitPolybius(FILE *fi, FILE *fo, int d){
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
int SetKeyPolybius(FILE *kf){
	int ac[27];
	int c,kc=0,x,y=0,z;
	char tk[28];
	
	ErrorFlag=0;
	/* Read the key file. (Special. Removes J) */
	while((c=fgetc(kf))!=EOF&&kc<27){
		/* Fix lower case letters. Ignore all else. */
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			/* Remove the J */
			if(c!='J'){
				c-=65;
				tk[kc]=(char)c;
				kc++;
			}
		}
	}
	/* Return Error if count check fails. */
	if(kc>25){
		ErrorFlag=1;
		return 1;
	}
	/* Process key and check that it's valid. */
	for(x=0;x<25;x++)ac[x]=0;
	/* Count letters and copy key. */
	for(x=0;x<25;x++){
		z=tk[x];
		if(z>9)z--;
		ac[z]++;
		key[x][0]=z;
	}
	/* Valid keys will only have one of each letter. */
	for(x=0;x<25;x++){
		if(ac[x]!=1){
			ErrorFlag=1;
			return 1;
		}
		/* Make decrypt key. */
		key[key[x][0]][1]=x;
	}
	return 0;
}
int MainPolybius(void){
	int c,clm,row,x,y=0,z=0,yl=0,zl,nc=0;
	/* A simple version of the Caesar cipher */
	if(dir==0){
		/* Limit 6 groups per line or 66 char. */
		zl=6;
	}else{
		/* Limit 10 groups per line or 60 char. */
		zl=10;
	}
	while((c=fgetc(fin))!=EOF){
		if(dir==0){
			/* Encrypt mode */
			if(c>='a'&&c<='z')c-=32;
			/* Perform sub and write upper case only. */
			if(c>='A'&&c<='Z'){
				/* Fix the 'J' hole */
				if(c>'I')c--;
				/* Perform the substitution */
				x=key[c-65][dir];
				/* This is a mathematical version of the square */
				row=x/5;
				clm=x%5;
				/* Convert key index to coordinates */
				fputc(row+49,fout); /* Write row */
				fputc(clm+49,fout); /* Write column */
				yl=1;
			}
		}else{
			/* Decrypt mode */
			if(c>='0'&&c<='9'){
				/* Convert numbers to key index and decrypt. */
				if(nc==0){
					/* row */
					row=c-49;
					nc++;
				}else{
					/* column */
					clm=c-49;
					x=key[row*5+clm][dir];
					/* Restore the 'J' hole */
					if(x>=9)x++;
					x+=65;
					fputc(x,fout);
					yl=1;
					nc--;
				}
			}
		}
		if(yl==1){
			/* Make 5 letter groups */
			y++;
			if(y==5){
				fputc(32,fout);
				y=0;
				/* Limit groups per line */
				z++;
				if(z==zl){
					fputc(13,fout);
					fputc(10,fout);
					z=0;
				}
			}
			yl=0;
		}
	}
	/* Final line termination. */
	fputc(13,fout);
	fputc(10,fout);
	/* Trap uneven number count for decrypt. */
	if(nc!=0){
		printf("Ciphertext error. Unbalanced coordinate detected\n");
		ErrorFlag=1;
	}
	return ErrorFlag;
}
int DonePolybius(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsagePolybius(void){
	printf(" usage: Polybius M keyfile infile outfile\n");
	printf(" M (mode)= E (encrypt) or D (decrypt) mode\n");
	printf(" keyfile = 25 or 26* letter mixed alphabet key file\n");
	printf(" infile  = input file\n");
	printf(" outfile = output file\n");
	printf(" Encrypt = caesar E key.txt plain.txt cipher.txt\n");
	printf(" Decrypt = caesar D key.txt  cipher.txt plain.txt\n");
	printf("* The letter 'J' in the keyfile is ignored.\n");
}
