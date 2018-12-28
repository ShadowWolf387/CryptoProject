/***************************************************************************
* caesar.h
* The header file for the caesar.c
***************************************************************************/
/* Some controlls for the core main() program. */
#define ARGLMTL 4
#define ARGLMTU 4

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitWork(FILE *fi, FILE *fo,int s,int d);
int MainWork(void);
int DoneWork(void);
void UsageWork(void);
