/**************************************************************************
* Quagmire.c
* The aristocrat cipher (General letter substitution)
**************************************************************************/
#include <stdio.h>

#include "Quagmire.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int shft;
int dir;
char key[27][4];
char off[30];
int offsz;
int ind;

int InitQuagmire(FILE *fi, FILE *fo, int d){
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
int SetKeyQuagmire(FILE *kf){
	int ac[27];
	int c,kc=0,x;
	char tk[28];
	
	ErrorFlag=0;
	/* Read the key file. */
	/* Get plaintext key */
	while((c=fgetc(kf))!=EOF&&kc<27){
		if(c<32)break;
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
			return 2;
		}
		/* Make decrypt key. */
		key[key[x][0]][1]=x;
	}
	kc=0;
	/* Load ciphertext key*/
	while((c=fgetc(kf))!=EOF&&kc<27){
		if(c<32)break;
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
		key[x][2]=tk[x];
	}
	/* Valid keys will only have one of each letter. */
	for(x=0;x<26;x++){
		if(ac[x]!=1){
			ErrorFlag=1;
			return 2;
		}
		/* Make decrypt key. */
		key[key[x][2]][3]=x;
	}
	/* Load indicator offset */
	while((c=fgetc(kf))!=EOF&&kc<27){
		/* Skip White */
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z'))break;
	}
	ind=key[(c&31)-1][1];
	kc=0;
	/* get indicator key */
	while((c=fgetc(kf))!=EOF&&kc<27){
		/* Get letters */
		/* Fix lower case letters */
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'&&kc<29){
			c-=65;
			off[kc]=(char)c;
			kc++;
		}else{
			if(kc>0)break;
		}
	}
	offsz=kc;
	return 0;
}
int MainQuagmire(void){
	int c,w=0,x,y=0,z=0;
	/* Quagmire cipher */
	while((c=fgetc(fin))!=EOF){
		if(c>='a'&&c<='z')c-=32;
		x=c;
		/* Perform sub and write upper case only. */
		if(c>='A'&&c<='Z'){
			if(dir==0){
				c=key[x-65][1]-ind+key[off[w]][3]+52;
				while(c>25)c-=26;
				c=key[c][2];
			}else{
				c=key[x-65][3]-key[off[w]][3]+ind+52;
				while(c>25)c-=26;
				c=key[c][0];
			}
			w++;
			if(w==offsz)w=0;
			fputc(c+65,fout);
			/* Make 5 letter groups */
			y++;
			if(y==5){
				fputc(32,fout);
				y=0;
				/* Limit 10 groups per line or 60 char. */
				z++;
				if(z==10){
					fputc(13,fout);
					fputc(10,fout);
					z=0;
				}
			}
		}
	}
	/* Final line termination. */
	fputc(13,fout);
	fputc(10,fout);
	return ErrorFlag;
}
int DoneQuagmire(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsageQuagmire(void){
	printf(" usage: Quagmire M keyfile infile outfile\n");
	printf(" M (mode)= E (encrypt) or D (decrypt) mode\n");
	printf(" keyfile = two 26 letter keys and indicator\n");
	printf(" infile  = input file\n");
	printf(" outfile = output file\n");
	printf(" Encrypt = Quagmire E key.txt plain.txt cipher.txt\n");
	printf(" Decrypt = Quagmire D key.txt  cipher.txt plain.txt\n");
}
