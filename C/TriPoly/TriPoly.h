/***************************************************************************
* TriPoly.h
* The header file for the TriPoly.c
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 5
#define ARGLMTU 5

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitTriPoly(FILE *fi, FILE *fo,int d);
int SetKeyTriPoly(FILE *kf);
int MainTriPoly(void);
int DoneTriPoly(void);
void UsageTriPoly(void);
