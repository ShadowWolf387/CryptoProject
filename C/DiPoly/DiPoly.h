/***************************************************************************
* DiPoly.h
* The header file for the DiPoly.c
***************************************************************************/
/* Some controls for the core main() program. */
#define ARGLMTL 5
#define ARGLMTU 5

/* All public functions go here. Private function prototypes are in Caesar.c */
int InitDiPoly(FILE *fi, FILE *fo,int d);
int SetKeyDiPoly(FILE *kf);
int MainDiPoly(void);
int DoneDiPoly(void);
void UsageDiPoly(void);
