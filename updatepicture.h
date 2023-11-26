/*
 *     updatepicture.h
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: defines the methods for updatepicture.c which will creates 
 *              and update a Pnm_ppm picture, either by flipping it or 
 *              leaving it unchanged, and returns the updated picture.
 */


#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <mem.h>
#include "getmethod.h"

#ifndef UPDATEPICTURE_INCLUDED
#define UPDATEPICTURE_INCLUDED

Pnm_ppm updatePicture(Pnm_ppm picture, bool is_flipped);

#endif