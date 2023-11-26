/*
 *     rotate.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: Rotates a given Pnm_ppm and outputs the transformation
 */

#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include "cputiming.h" 

#ifndef ROTATE_INCLUDED
#define ROTATE_INCLUDED

//typedef A2Methods_UArray2 A2;

double rotate(int rotation, Pnm_ppm picture, CPUTime_T timer);

void apply90(int i, int j, A2Methods_UArray2 a, void *elem, void *cl);
void apply180(int i, int j, A2Methods_UArray2 a, void *elem, void *cl);
void apply270(int i, int j, A2Methods_UArray2 a, void *elem, void *cl);

#endif
