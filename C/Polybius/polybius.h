/***************************************************************************
* Polybius.h
* The header file for the Polybius.c
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 5
#define ARGLMTU 5

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitPolybius(FILE *fi, FILE *fo,int d);
int SetKeyPolybius(FILE *kf);
int MainPolybius(void);
int DonePolybius(void);
void UsagePolybius(void);
