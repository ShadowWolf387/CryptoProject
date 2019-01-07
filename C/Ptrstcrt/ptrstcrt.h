/***************************************************************************
* Ptrstcrt.h
* The header file for the Ptrstcrt.c
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 5
#define ARGLMTU 5

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitPtrstcrt(FILE *fi, FILE *fo,int d);
int SetKeyPtrstcrt(FILE *kf);
int MainPtrstcrt(void);
int DonePtrstcrt(void);
void UsagePtrstcrt(void);
