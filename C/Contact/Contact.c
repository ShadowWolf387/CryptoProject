/**************************************************************************
* Contact.c
* A placeholder for future projects
**************************************************************************/
#include <stdio.h>

#include "Contact.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;

int cntk[26][26][2],cct[26];
int lc;

int InitContact(FILE *fi, FILE *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int MainContact(void){
	int c,c1,c2,c3,x,y;
 /* Initialize arrays. */
  for(x=0;x<26;x++){
  	cct[x]=0;
  	for(y=0;y<26;y++){
    	cntk[x][y][0]=cntk[x][y][1]=0;
    }
  }
	/* Count contacts */
	while((c=fgetc(fin))!=EOF){
		/* Only count letters. */
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			/* Shift letters through window. */
			c1=c2;
			c2=c3;
			c3=c-65;
			lc++;
			/* Make sure the window is loaded then count. */
      if(lc<3) continue;
      /* sum left contact info */
      cntk[c2][c3][0]++;
      /* sum right contact info */
      cntk[c2][c1][1]++;
      /* sum total frequency count */
      cct[c2]++;
		}
	}
	return ErrorFlag;
}
int DoneContact(void){
	int x,y,z;
	char buf[30];
	/* Write contact list file. */
  /* Build initial consonant and vowel lines */
  for(x=0;x<26;x+=4){
  	for(z=0;z<4;z++){
			if(x+z<26)fprintf(fout,"%9d %c            ",cct[x+z],x+z+65);
  	}
  	fprintf(fout,"\n");
  	for(z=0;z<4;z++){
  		if(x+z<26)fprintf(fout,"----------|----------  ");
  	}
  	fprintf(fout,"\n");
  	for(y=0;y<26;y++){
  		/* Print contact lists */
  		for(z=0;z<4;z++){
 				if(x+z<26){ 					
 					sprintf(buf,"%9d %c %d            ",cntk[x+z][y][0],y+65,cntk[x+z][y][1]);
 					buf[23]=0;
 					fprintf(fout,"%s",buf);
				}
  		}
  		fprintf(fout,"\n");
  	}
  	fprintf(fout,"\n\n");
	}
  fprintf(fout,"Total letters = %d",lc);
	return ErrorFlag;
}
void UsageContact(void){
	printf(" usage: Contact infile outfile\n");
	printf(" Makes a contact count. Ignores word divisions.");
	printf(" Uses a moving window the same as the trigram counter.");
}
