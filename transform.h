/*
 *     transform.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: defines the methods for transform.c which will apply
 *              transformations to an image
 */


#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include "cputiming.h" 

#ifndef TRANSFORM_INCLUDED
#define TRANSFORM_INCLUDED

typedef A2Methods_UArray2 A2;

void transformPic(int operation, FILE *file, int rotation, int direction, 
                char* time_file_name, A2Methods_T method);


#endif