/*
 *     getmethod.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework#3
 *     summary: Caller function used to get the current method of a
                Pnm_ppm picture
 */

#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

#ifndef GETMETHOD_INCLUDED
#define GETMETHOD_INCLUDED

const struct A2Methods_T *getMethod(Pnm_ppm picture);

#endif