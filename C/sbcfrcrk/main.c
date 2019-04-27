#include <stdio.h>
#include <conio.h>
#include "conio2.h"

#define MAXSZ 600

char cfrtxt[MAXSZ+1];
char subtbl[26];
int fc[26];
int pstn;
int ltrcnt;
float ic,s;

int onekey(void);
void show(void);
void keyread(int ky);

int main(int argc, char *argv[]){
	int c,x;
	FILE *fi,*fo;
	if(argc>2&&argc<3){
		printf("Usage: subcfr infile <savefile>\n");
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
			cfrtxt[x]=c;
			fc[c-65]++;
			x++;
		}
	}
	fclose(fi);
	cfrtxt[x]=0;
	ltrcnt=x;
	/* Initialize */
	clrscr();
	pstn=0;
	for(x=0;x<26;x++){
		if(argc!=3)subtbl[x]=32;
		s+=(float)(fc[x]*(fc[x]-1));
	}
	ic=s/(float)(ltrcnt*(ltrcnt-1));
	/* Do work loop */
	gotoxy(1,21);
	textcolor(11);
	for(x=0;x<26;x++)cprintf("  %c",x+65);
	gotoxy(1,22);
	textcolor(10);
	for(x=0;x<26;x++)cprintf(" %2d",fc[x]);
	gotoxy(1,24);
	cprintf("IC = %f  (0.0667)",ic);
	do{
		show();
		c=onekey();
		keyread(c);
	}while(c!=27);
	if(argc==3){
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
void show(void){
	int c,x;
	
	x=0;
	textcolor(10);
	while(x<ltrcnt){
		if(x%75==0)gotoxy(3,(x/75)*2+2);
		cprintf("%c",cfrtxt[x]);
		x++;
	}
	x=0;
	textcolor(12);
	while(x<ltrcnt){
		if(x%75==0)gotoxy(3,(x/75)*2+3);
		c=cfrtxt[x];
		if(c>='A'&&c<='Z')c=subtbl[c-65];
		cprintf("%c",c);
		x++;
	}
	textcolor(11);
	gotoxy(14,18);
	cprintf(" A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ");
	gotoxy(14,19);
	textcolor(12);
	for(x=0;x<26;x++)cprintf(" %c",subtbl[x]);
	textcolor(15);
	gotoxy(14+pstn*2,18);
	cprintf("|");
	gotoxy(16+pstn*2,18);
	cprintf("|");
	textcolor(7);
}
void keyread(int ky){
	switch(ky){
		case 32:
			if(ky=32){
				subtbl[pstn]=32;
			}
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
			if(ky>='A'&&ky<='Z')ky+=32;
			if(ky>='a'&&ky<='z'){
				subtbl[pstn]=ky;
			}
			break;
	}
}
