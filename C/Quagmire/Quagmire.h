/***************************************************************************
* Quagmire.h
* The header file for the Quagmire.c
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 5
#define ARGLMTU 5

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitQuagmire(FILE *fi, FILE *fo,int d);
int SetKeyQuagmire(FILE *kf);
int MainQuagmire(void);
int DoneQuagmire(void);
void UsageQuagmire(void);
