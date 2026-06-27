#ifndef KPM_DEFINES_H
#define KPM_DEFINES_H

// ROWS
#define R0 16
#define R1 17
#define R2 18
#define R3 19

// COLUMNS
#define C0 20
#define C1 21
#define C2 22
#define C3 23

// Functions
void initKPM(void);

unsigned int colscan(void);

unsigned int rowcheck(void);

unsigned int colcheck(void);

unsigned int keyscan(void);

int ReadNum(void);

#endif
