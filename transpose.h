/*
 *     transpose.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: Transposes a given Pnm_ppm and outputs the transformation
*/


#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include "cputiming.h" 

#ifndef TRANSPOSE_INCLUDED
#define TRANSPOSE_INCLUDED

double transpose(Pnm_ppm picture, CPUTime_T timer);

void applyTrans(int i, int j, A2Methods_UArray2 a, void *elem, void *cl);

#endif

