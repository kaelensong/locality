/*
 *     flip.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: Flips a given Pnm_ppm picture and outputs the transformation
 */

#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include "cputiming.h" 

#ifndef FLIP_INCLUDED
#define FLIP_INCLUDED

double flip(int direction, Pnm_ppm picture, CPUTime_T timer);

void applyHorz (int i, int j, A2Methods_UArray2 a, void *elem, void *cl);
void applyVert(int i, int j, A2Methods_UArray2 a, void *elem, void *cl);

#endif
