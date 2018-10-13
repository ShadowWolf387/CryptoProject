/***************************************************************************
* work.h
* The header file for the work.c placeholder
***************************************************************************/
/* Some controlls for the core main() program. */
#define ARGLMTL 3
#define ARGLMTU 3

/* All public functions go here. Private function prototypes are in work.c */
int InitWork(FILE *fi, FILE *fo);
int MainWork(void);
int DoneWork(void);
void UsageWork(void);
