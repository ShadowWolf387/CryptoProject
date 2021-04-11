#include <stdio.h>
//#define LINUX

#ifdef LINUX
#include "coniolnx.h"
#else
#include <conio.h>
#include "conio2.h"
#endif


#define MAXSZ 600 /* Also limits frequency counts to 2 digits at 600. */

/* Colors defined here to make finding them easier. */
#define CTXTCLR LIGHTGREEN
#define PTXTCLR YELLOW
#define CRSRCLR WHITE
#define ALPHCLR LIGHTGREEN
#define CNTCLR	YELLOW
#define NORMCLR LIGHTGRAY

char cfrtxt[MAXSZ+1];
char subtbl[26];
int fc[26];
int pstn;
int txtcnt,ltrcnt;
float ic,s;
int c1,c2,c3,ct[26][26],rs[26],vl[5],vc;

int onekey(void);
void show(void);
void keyread(int ky);

int main(int argc, char *argv[]){
	int c,x;
	int y,z;
	FILE *fi,*fo;
	
#ifdef LINUX
	inicjuj();
#endif

	if(argc<2||argc>3){
		printf("Usage: subcfr infile <keyfile>\n");
		printf("Text size limited to %d chars.\n",MAXSZ);
		return 1;
	}
	if((fi=fopen(argv[1],"rt"))==NULL){
		printf("Can't open infile\n");
		return 1;
	}
	if(argc==3){
		fo=fopen(argv[2],"rt");
		/* Read save file */
		for(x=0;x<26;x++){
			c=fgetc(fo);
			if(c==EOF)break;
			if(c>='A'&&c<='Z')c+=32;
			if(c>='a'&&c<='z'){
				subtbl[x]=c;
			}
		}
		fclose(fo);
	}
	/* get file */
	x=0;
	while((c=fgetc(fi))!=EOF&&x<MAXSZ){
		if(c==10)c=32;
		if(c>='a'&&c<='z')c-=32;
		if(c>=32&&c<=126){
			cfrtxt[x]=c; /* text */
			if(c>='A'&&c<='Z'){
				fc[c-65]++; /* frequency */
				c3=c2; /* Build Sukhotin contact table */
				c2=c1;
				c1=c-65;
				if(x>0)ct[c2][c1]++;
				if(x>1)ct[c2][c3]++;
			}
			x++;
		}
	}
	fclose(fi);
	cfrtxt[x]=0;
	txtcnt=x;
	ct[c1][c2]++; /* Add last contact for Sukhotin table */
	/* Initialize */
	clrscr();
	ltrcnt=pstn=0;
	for(x=0;x<26;x++){
		if(argc!=3)subtbl[x]=32;
		s+=(float)(fc[x]*(fc[x]-1));
		ltrcnt+=fc[x];
	}
	ic=s/(float)(ltrcnt*(ltrcnt-1));
	for(x=0;x<26;x++){ /* Sum Sukhotin contact table rows */
		ct[x][x]=0; /* Clear the diagonal for all the letters */
		for(y=0;y<26;y++){
			rs[x]+=ct[x][y];
		}
	}
	z=vc=0;
	do{
		for(x=0;x<26;x++){ /* Find highest row */
			if(rs[x]>rs[z])z=x;
		}
		if(rs[z]>0){ /* Save as vowel if highest number positive. */
			vl[vc]=z+65;
			vc++;
			for(y=0;y<26;y++){
				rs[y]-=(ct[z][y]+ct[z][y]); /* Subtract 2x vowel column from rows */
			}			
			rs[z]=1; /* Remove vowel from row sums. */
		}
	}while(rs[z]>0&&vc<5); /* exit if 5 vowels found or sums are all negative. */
	/* Do work loop */
	gotoxy(1,21);
	textcolor(ALPHCLR);
	for(x=0;x<26;x++)cprintf("  %c",x+65);
	gotoxy(1,22);
	textcolor(CNTCLR);
	for(x=0;x<26;x++)cprintf(" %2d",fc[x]);
	gotoxy(1,24);
	cprintf("Count = %d   IC = %f   Vowels = ",ltrcnt,ic);
	for(x=0;x<vc;x++)cprintf("%c",vl[x]);
	do{ /* Control loop */
		show();
		c=onekey();
		keyread(c);
	}while(c!=27);
	if(argc==3){ /* Save key if given a file name. */
		if((fo=fopen(argv[2],"wt"))==NULL){
			printf("Can't open savefile\n");
			return 1;
		}
		/* Write save file */
		for(x=0;x<26;x++){
				fputc(subtbl[x],fo);
		}
		fclose(fo);
	}
	return 0;
}
int onekey(void){
	static int c;
	/* Wait for a key press */
	while(kbhit()==0);
	c=getch();
	/* Get 2nd char if an extended key */
	if(c==0||c==224){
		c=getch()|256;
	}
	return(c);
}
void show(void){ /* Write current screen data */
	int c,x;
	
	x=0;
	textcolor(CTXTCLR);
	while(x<txtcnt){
		if(x%75==0)gotoxy(3,(x/75)*2+2);
		cprintf("%c",cfrtxt[x]);
		x++;
	}
	x=0;
	textcolor(PTXTCLR);
	while(x<txtcnt){
		if(x%75==0)gotoxy(3,(x/75)*2+3);
		c=cfrtxt[x];
		if(c>='A'&&c<='Z')c=subtbl[c-65];
		cprintf("%c",c);
		x++;
	}
	textcolor(ALPHCLR);
	gotoxy(14,18);
	cprintf(" A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ");
	gotoxy(14,19);
	textcolor(PTXTCLR);
	for(x=0;x<26;x++)cprintf(" %c",subtbl[x]);
	textcolor(CRSRCLR);
	gotoxy(14+pstn*2,18);
	cprintf("|");
	gotoxy(16+pstn*2,18);
	cprintf("|");
	textcolor(NORMCLR);
}
void keyread(int ky){ /* Decides what to do with key press. */
	switch(ky){
		case 32:
			subtbl[pstn]=32;
			break;
		case 331:
			pstn--;
			if(pstn<0)pstn=25;
			break;
		case 333:
			pstn++;
			if(pstn>25)pstn=0;
			break;
		default:
			if(ky>='A'&&ky<='Z'){
				pstn=ky-65;
				return;
			}
			if(ky>='a'&&ky<='z'){
				subtbl[pstn]=ky;
			}
			break;
	}
}
