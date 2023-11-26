/*
 *     transform.c
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: defines the methods for transform.h which will apply
 *              transformations to an image
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cputiming.h" 
#include "transform.h"
#include "assert.h"
#include "a2methods.h"
#include "pnm.h"
#include "mem.h"
#include "flip.h"
#include "rotate.h"
#include "transpose.h"
#include "timerfile.h"


/********** transformPic ********
 * Purpose: call all appropriate functions that will apply the correct
 *          transformation to an image and starts the timer if the user
 *          requests
 * Inputs:
 *              int operation: integers 1, 2,  3
 *              FILE* file: a file pointer to the image to be transformed
 *              int rotation: the amount of degrees to be rotated
 *              int direction: the direction to be flipped 
 *                              (horizontal or vertical)
 *              char* time_file_name: the filename where the timer's results
 *                                    will be stored
 *              A2Methods_T method: method to be used (block-major, 
 *                                      row-major, or, column-major)
 * Return:  no direct returns, outputs image to stdout
 * Expects: The picture or timer to not be null
 * NOTES:  Will CRE if memory allocation fails for timer
 ************************/
void transformPic(int operation, FILE* file, int rotation, int direction, 
                        char* time_file_name, A2Methods_T method) 
{
        Pnm_ppm picture;
        //picture = Pnm_ppmread(stdin, method);
        picture = Pnm_ppmread(file, method);
        assert(picture != NULL);
        fclose(file); 
        
        /* start CPU timer */
        CPUTime_T timer;
        timer = CPUTime_New();
        assert(timer != NULL);
        double time_used;

        if (operation == 1){
                time_used = rotate(rotation, picture, timer);
        } else if (operation == 2){ 
                time_used = flip(direction, picture, timer);
        } else if (operation == 3){ 
                time_used = transpose(picture, timer);
        }
        
        timerFile(time_used, time_file_name, picture);
        (void) time_file_name;
        CPUTime_Free(&timer);
        Pnm_ppmfree(&picture);
}