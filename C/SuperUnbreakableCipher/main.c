/******************************************************
* unbrkbl.c
* This is the cipher system that most programmers at
* least think about writing a program for.
*
* Lots of comments to help with understanding.
*
* The Super Unbreakable Cipher Program
*       (extreme sarcasm intended)
******************************************************/
#include <stdio.h>
#include <string.h>

int MyRnd(int seed);

int main(int argc, char *argv[]){
  int dir=0,key=0;
  int c,d,x,y;
  FILE *fi,*fo;
  /* Check for args */  
  if(argc!=5){
    printf("   Usage: unbrkbl d key infile outfile\n");
    printf("      d = Direction: e or d (encrypt or decrypt)\n");
    printf("    Key = an integer from 1 to 714024\n");
    printf(" infile = input path/filename\n");
    printf("outfile = output path/filename\n");
    return 1;
  }
  /* Set cipher mode. */
  switch(argv[1][0]){
    case 'e':
      dir=1;
      break;
    case 'd':
      dir=-1;
      break;
    default:
      printf("ERROR: Illegal direction argument.\n");
      return 1;
  }
  /* Set key */
  x=strlen(argv[2]);
  for(y=0;y<x;y++)key=key*10+argv[2][y]-48;
  if(key<1||key>714024){
    printf("ERROR: Illegal key value.\n");
    return 1;
  }
  MyRand(key);
  /* Open files */
	if((fi=fopen(argv[3],"rt"))==NULL){
		printf("ERROR: Can't open input file '%s'\n",argv[3]);
		return(1);
  }
	if((fo=fopen(argv[4],"wt"))==NULL){
		printf("ERROR: Can't open output file '%s'\n",argv[4]);
		fclose(fi);
		return(1);
  }
  /* Run the cipher */
  while((c=getc(fi))!=EOF){
    d=c;
    c&=95;
    if(c>='A'&&c<='Z'){
      /* 39 is 65-26 to allow for subtraction in decrypt mode. */
      d=(c-39+dir*MyRand())%26+65;
    }
    fputc(d,fo);
  }
  /* All done */
  fclose(fi);
  fclose(fo);
  return 0;
}
int MyRand(int seed){
  static unsigned int rnd, last;
  if(seed>0)last=seed;
  rnd=(1366*last+150889)%714025;
  last=rnd;
  rnd=last%26;
  return rnd;
}
