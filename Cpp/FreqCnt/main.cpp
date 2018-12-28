/***********************************************************************
* main.cpp
* The core main program in C++.
* This is mostly the same as the C version
***********************************************************************/
/* Include any libraries needed. */
#include <fstream>
#include <iostream>
/* Also include the work header. */
#include "freqcnt.hpp"
using namespace std;

/* Allow the programs to function in a batch or script environment. */
int main(int argc, char *argv[]){
/* Declare the few variables needed. */
	int errcode;
	ifstream fi;
	ofstream fo;
	Work FrCnt;

/* Error check argc and display usage instructions. */
	if(argc<ARGLMTL||argc>ARGLMTU){
		FrCnt.UsageWork();
		/* Return with an error exit. */
		return 1;
	}
/* Open files as needed and trap errors. */
	fi.open(argv[1]);
	if(fi.good()==false){
		cerr<<"Can't open input file "<<argv[1]<<endl;
		return 1;
	}
	fo.open(argv[2]);
	if(fo.good()==false){
		cerr<<"Can't open output file "<<argv[2]<<endl;
		fi.close();
		return 1;
	}
/* Initialize the work function. */
	if((errcode=FrCnt.InitWork(&fi,&fo))!=0){
		/* Init failed */
		return errcode;
	}
/* Call the work function. */
	if((errcode=FrCnt.MainWork())!=0){
		/* Main failed */
		return errcode;
	}
/* Clean up things after work is done. */
	if((errcode=FrCnt.DoneWork())!=0){
		/* Done failed */
		return errcode;
	}
/* Close files that were opened. */
	fi.close();
	fo.close();
/* Exit no error */
	return 0;
}
