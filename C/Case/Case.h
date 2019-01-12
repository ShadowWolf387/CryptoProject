/***************************************************************************
* Case.h
***************************************************************************/
/* Some controlls for the core main() program. */
#define ARGLMTL 4
#define ARGLMTU 4

/* All public functions go here. Private function prototypes are in Case.c */
int InitCase(FILE *fi, FILE *fo,int d);
int MainCase(void);
int DoneCase(void);
void UsageCase(void);
