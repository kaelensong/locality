/*
 *     transpose.c
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
#include "getmethod.h"
#include "transpose.h" 
#include "updatepicture.h"

/********** applyTrans ********
 * 
 * apply function for transposing a 2D array element.
 * 
 * Inputs:
 *         int i: The column index of the element being processed.
 *         int j: The row index of the element being processed.
 *         A2 a: The 2D array being operated on (not used in this function).
 *         void *elem: Pointer to the source element to be transposed.
 *         void *cl: Pointer to the Pnm_ppm structure representing
 *                        the destination image.
 * Effects: Adds current pixel to a Pnm_ppm given by void *cl
 ************************/
void applyTrans(int i, int j, A2Methods_UArray2 a, void *elem, void *cl)
{
        Pnm_ppm newPic = cl;
        const struct A2Methods_T *method = getMethod(newPic);
        Pnm_rgb newLoc = (Pnm_rgb)(method->at(newPic->pixels, j, i));
        *newLoc = *(Pnm_rgb) elem;
        (void)a;
}

/********** transpose ********
 * 
 * Transposes the given image (swaps rows and columns), starts a timer, and 
 * prints out the transposed image.
 * 
 * Inputs:
 *         Pnm_ppm picture: the picture to be transposed.
 *         CPUTime_T timer: the time object to measure execution time.
 *              
 * Return: double containing the time taken to transpose the image in seconds.
 * 
 * 
 ************************/
double transpose(Pnm_ppm picture, CPUTime_T timer)
{
        Pnm_ppm updated_pic = updatePicture(picture, true);
        const struct A2Methods_T *method = getMethod(picture);
        CPUTime_Start(timer);
        double time_used; 
        method->map_default(picture->pixels, applyTrans, updated_pic);
        time_used = CPUTime_Stop(timer);
        Pnm_ppmwrite(stdout, updated_pic);
        Pnm_ppmfree(&updated_pic);
        return time_used;
}
