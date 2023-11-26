/*
 *     flip.c
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
#include "getmethod.h"
#include "flip.h"
#include "updatepicture.h"

/********** applyVert ********
 * 
 * apply function for horizontal flipping of a 2D array element.
 * 
 * Inputs:
 *         int i: The column index of the element being processed.
 *         int j: The row index of the element being processed.
 *         A2 a: The 2D array being operated on (not used in this function).
 *         void *elem: Pointer to the source element to be copied (Pnm_rgb)
 *         void *cl: Pointer to the Pnm_ppm structure representing 
                  the destination image.
 * 
 * Returns: -
 * Effects: Adds current pixel to a Pnm_ppm given by void *cl
 ************************/
void applyHorz (int i, int j, A2Methods_UArray2 a, void *elem, void *cl)
{
        Pnm_ppm newPic = cl;
        const struct A2Methods_T *method = getMethod(newPic);
        int loc = newPic->width - i - 1;
        Pnm_rgb newLoc = (Pnm_rgb)(method->at(newPic->pixels, loc, j));
        *newLoc = *(Pnm_rgb) elem;
        (void)a;
}

/********** applyVert ********
 * 
 * apply function for vertical flipping of a 2D array element.
 * 
 * Inputs:
 *         int i: The column index of the element being processed.
 *         int j: The row index of the element being processed.
 *         A2 a: The 2D array being operated on (not used in this function).
 *         void *elem: Pointer to the source element to be copied (Pnm_rgb)
 *         void *cl: Pointer to the Pnm_ppm structure representing the
                  destination image.
 * 
 * Returns: -
 * Effects: Adds current pixel to a Pnm_ppm given by void *cl
 ************************/
void applyVert(int i, int j, A2Methods_UArray2 a, void *elem, void *cl)
{
        Pnm_ppm newPic = cl;
        const struct A2Methods_T *method = getMethod(newPic);
        int loc = newPic->height - j - 1;
        Pnm_rgb newLoc = (Pnm_rgb)(method->at(newPic->pixels, i, loc));
        *newLoc = *(Pnm_rgb) elem;
        (void)a;
}

/********** flip ********
 * 
 * Flips the given image horizontally or vertically, starts a timer, and prints
 * out the flipped image.
 * 
 * Inputs:
 *         int direction: 0 for horizontal flip, 1 for vertical flip
 *         Pnm_ppm picture: the picture to be flipped
 *         CPUTime_T timer: the time object to measure execution time
 *              
 * Return: double containing the time taken to flip the image in seconds
 *  
 ************************/
double flip(int direction, Pnm_ppm picture, CPUTime_T timer)
{
        const struct A2Methods_T *method = getMethod(picture);
        assert(direction == 0 || direction == 1);
        Pnm_ppm updated_pic = updatePicture(picture, false);
        double time_used;

        if(direction == 0){
                CPUTime_Start(timer);
                method->map_default(picture->pixels, applyHorz, updated_pic);
                time_used = CPUTime_Stop(timer);
        } else {
                CPUTime_Start(timer);
                method->map_default(picture->pixels, applyVert, updated_pic);
                time_used = CPUTime_Stop(timer);
        }
        
        Pnm_ppmwrite(stdout, updated_pic);
        Pnm_ppmfree(&updated_pic);
        return time_used;
}