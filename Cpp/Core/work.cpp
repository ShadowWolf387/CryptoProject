/**************************************************************************
* work.cpp
* A placeholder for future projects.
* As this is more or less a template, some things are not used.
**************************************************************************/
#include <iostream>
#include "work.hpp"

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
	/* A simple version of Rot13 */
	while(fin->eof()==false){
		fin->get(c);
		/* Perform rot13 on lower case only. */
		if(c>='a'&&c<='z'){
			c+=13;
			if(c>'z')c-=26;
		}
		/* Perform rot13 on upper case only. */
		if(c>='A'&&c<='Z'){
			c+=13;
			if(c>'Z')c-=26;
		}
		fout->put(c);
	}
	return ErrorFlag;
}
int Work::DoneWork(void){
	/* Nothing to do here. */
	return ErrorFlag;
}
void Work::UsageWork(void){
	// Just a brief description and/or usage instruction.
	// This will always be cipher specific.
	cout<<" usage: work <infile> <outfile>\n";
}
