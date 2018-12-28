/**************************************************************************
* freqcnt.cpp
* A basic letter frequency counter.
**************************************************************************/
#include <iostream>
#include <string>
#include "freqcnt.hpp"

/* These variables need to be at least 32 bit. */
unsigned long fc[26];
unsigned long tc;
unsigned long lc;
int srt[26];

Work::Work(){
	//Does nothing. May get used in future projects.
}
Work::~Work(){
	//Does nothing. May get used in future projects.
}
int Work::InitWork(ifstream *fi, ofstream *fo){
	/* If this module is reused, make sure ErrorFlag is reset. */
	ErrorFlag=0;
	/* Store the file pointers for global use here. */
	fin=fi;
	fout=fo;
	/* Nothing else needed here */
	return ErrorFlag;
}
int Work::MainWork(void){
	char c;
		int cc,f,x;
	/* Read and count */
	while(fin->eof()==false){
		fin->get(c);
		/* Count total file length. */
		tc++;
		/* Fix lower to upper case */
		if(c>='a'&&c<='z')c-=32;
		/* Count letters and total letters. */
		if(c>='A'&&c<='Z'){
			x=c-65;
			fc[x]++;
			lc++;
		}
	}
	/* Init sort array. */
	for(x=0;x<26;x++)srt[x]=x;
	/* Simple sort by frequency. */
	do{
		f=0;
		for(x=0;x<25;x++){
			if(fc[srt[x+1]]>fc[srt[x]]){
				cc=srt[x];
				srt[x]=srt[x+1];
				srt[x+1]=cc;
				f=1;
			}
		}
		/* Loop until no swaps. */
	}while(f!=0);
	return ErrorFlag;
}
int Work::DoneWork(void){
	char x,buf[50];
	/* Print the frequencies and counts. */
	for(x=0;x<26;x++){
		sprintf(buf,"  %10d",fc[x]);
		*fout << buf;
		*fout << "  " << (char)x+65 << "    " << (char)srt[x]+65 << "  ";
		fout->width(10);
		*fout << fc[srt[x]];
		*fout << endl;
	}
	*fout << endl << "Total letter count = " << lc << endl;
	*fout << "File byte count = ";
	*fout << tc << endl;
	return ErrorFlag;
}
void Work::UsageWork(void){
	// Just a brief description and/or usage instruction.
	// This will always be cipher specific.
	cout<<" usage: work <infile> <outfile>\n";
}
