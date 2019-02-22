/**************************************************************************
* TriPoly.c
* The aristocrat cipher (General letter substitution)
**************************************************************************/
#include <stdio.h>

#include "TriPoly.h"
/* Private function prototypes go here. */

/* Local global variables. */
FILE *fin,*fout;
int ErrorFlag;
int shft;
int dir;
char key[3][27];
char dcrpt[3][5][5],ecrpt[3][26][2];

int InitTriPoly(FILE *fi, FILE *fo, int d){
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
int SetKeyTriPoly(FILE *kf){
	int a,c,kc=0,k=0,r,s,x,y;
	
	ErrorFlag=0;
	/* Read the key file. */
	while((c=fgetc(kf))!=EOF&&k<3){
		/* Fix lower case letters. Ignore all else. */
		if(c>='a'&&c<='z')c-=32;
		if(c>='A'&&c<='Z'){
			key[k][kc]=(char)c;
			kc++;
			if(kc>26)return 1;
		}
		if(c==10||c==13&&kc!=0){
			key[k][kc]=0;
			kc=0;
			k++;
		}
	}
	/* Fix last key if newline missing. */
	if(k==2&&kc>=25){
		key[k][kc]=0;
		k++;
	}
#ifdef TEST
	printf("Keys:\n%s\n%s\n%s\nk = %d  kc = %d  dir = %d\n"
	,key[0],key[1],key[2],k,kc,dir);
#endif	
	/* Return Error if count check fails. */
	if(k!=3){
		ErrorFlag=1;
		return 1;
	}
	/* Build keys */
	for(x=0;x<3;x++){
		s=r=c=0;
		for(y=0;y<25;y++){
			/* deal with J if found */
			do{
				a=key[x][y+s]-65;
				if(a==9)s=1;
			}while(a==9);
			ecrpt[x][a][0]=r;
			ecrpt[x][a][1]=c;
			dcrpt[x][r][c]=a;
			c++;
			if(c>4){
				c=0;
				r++;
			}
		}
	}
#ifdef TEST	
	for(x=0;x<5;x++){
		for(y=0;y<3;y++){
			printf("    ");
			for(a=0;a<5;a++){
				printf("%c",dcrpt[y][x][a]+65);
			}
		}
		printf("\n");
	}
	for(x=0;x<3;x++){
		for(y=0;y<26;y++){
			if(y==13)printf("\n");
			printf("%c%c%c  ",y+65,ecrpt[x][y][0]+48,ecrpt[x][y][1]+48);
		}
		printf("\n");
	}
#endif	
	return 0;
}
int MainTriPoly(void){
	int c,x;
	int it[3][2],l,t,wc;
	
	/* A trigraphic polybius square cipher */
	t=wc=l=0;
	while((c=fgetc(fin))!=EOF){
		c-=65;
		if(c>26)c-=32;
		if(c==9)c=8;
		if(c>=0&&c<26){
			it[t][0]=ecrpt[t][c][0];
			it[t][1]=ecrpt[t][c][1];
			t++;
			if(t>2){
				t=0;
				if(dir==0){ /* Encrypt */
					fputc(dcrpt[0][it[0][1]][it[1][0]]+65,fout);
					fputc(dcrpt[1][it[0][0]][it[2][1]]+65,fout);
					fputc(dcrpt[2][it[1][1]][it[2][0]]+65,fout);
				}else{ /* Decrypt */
					fputc(dcrpt[0][it[1][0]][it[0][0]]+65,fout);
					fputc(dcrpt[1][it[0][1]][it[2][0]]+65,fout);
					fputc(dcrpt[2][it[2][1]][it[1][1]]+65,fout);
				}
				wc++;
				if(wc>1){
					wc=0;
					l++;
					if(l>9){
						l=0;
						fputc(13,fout);
						fputc(10,fout);
					}else{
						fputc(32,fout);
					}
				}
			}
		}
	}
	return ErrorFlag;
}
int DoneTriPoly(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void UsageTriPoly(void){
	printf(" usage: TriPoly M keyfile infile outfile\n");
	printf(" M (mode)= E (encrypt) or D (decrypt) mode\n");
	printf(" keyfile = three 26 letter mixed alphabets key file\n");
	printf(" infile  = input file\n");
	printf(" outfile = output file\n");
	printf(" Encrypt = TriPoly E key.txt ptxt.txt ctxt.txt\n");
	printf(" Decrypt = TriPoly D key.txt ptxt.txt ctxt.txt\n");
}
