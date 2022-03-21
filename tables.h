#ifndef _TABLES_H_
#define _TABLES_H_

#define NUMBER_OF_LENGTHS	9
#define NUMBER_OF_VALUES	9

#ifdef EXTERN
#define EXTERN 
#else
#define EXTERN extern
#endif


EXTERN double const BOARD_LEVEL[3][NUMBER_OF_LENGTHS];
EXTERN int const NUMBER_LEVEL[3][NUMBER_OF_VALUES];
EXTERN int const DIFFICULT_LEVEL[3][3];
	

#endif /* tables.h */