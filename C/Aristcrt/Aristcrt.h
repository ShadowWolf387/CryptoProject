/***************************************************************************
* aristcrt.h
* The header file for the aristcrt.c
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 5
#define ARGLMTU 5

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitAristcrt(FILE *fi, FILE *fo,int d);
int SetKeyAristcrt(FILE *kf);
int MainAristcrt(void);
int DoneAristcrt(void);
void UsageAristcrt(void);
