/***************************************************************************
* PosCnt.h
* The header file for the PosCnt.c
***************************************************************************/
/* Some controlls for the core main() program. */
#define ARGLMTL 3
#define ARGLMTU 3

/* All public functions go here. Private function prototypes are in work.c */
int InitPosCnt(FILE *fi, FILE *fo);
int MainPosCnt(void);
int DonePosCnt(void);
void UsagePosCnt(void);
