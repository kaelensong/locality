/*
 *     timerfile.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: Writes timing information to a file, 
 *               including:
 *                      total time taken, 
 *                      the number of pixels in the picture
 *                      time per pixel.
 */

#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include "cputiming.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

void timerFile(double time_used, char* time_file_name, Pnm_ppm picture);

#endif
