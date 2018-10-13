/***************************************************************************
* work.h
* The header file for the work.cpp placeholder
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 3
#define ARGLMTU 3

#include <fstream>
using namespace std;
/*************************************************************************
* The work class
* All the ciphers and utilities will have this base form.
* Most ciphers and utilities won't need to actually use the Ctor and Dtor.
*************************************************************************/
class Work{
	public:
		Work(); // Ctor. Most of the time this will be empty.
		~Work(); // Dtor. Most of the time this will be empty.
		int InitWork(ifstream *fi, ofstream *fo); // Initializes. Could be an alt Ctor
		int MainWork(void); // The main cipher or utility function.
		int DoneWork(void);	// Saves results and cleans up. Could be a Dtor.
		void UsageWork(void);
	private:
		ifstream *fin;
		ofstream *fout;
		int ErrorFlag;
};
