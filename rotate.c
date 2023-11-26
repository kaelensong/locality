/*
 *     rotate.c
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
#include "getmethod.h"
#include "rotate.h"
#include "updatepicture.h"

/********** apply90 ********
 * 
 * Apply function used in mapping that will add each element
 *      to Pnm_ppm newpic in the specifed location when the image is rotaed
 *      90 degrees
 * 
 * Inputs: 
 *         int i: The column index of the element being processed.
 *         int j: The row index of the element being processed.
 *         A2 a: The 2D array being operated on (not used in this function).
 *         void *elem: Pointer to the source element to be copied (Pnm_rgb)
 *         void *cl: Pointer to the Pnm_ppm structure representing the
 *                   destination image.
 *
 * Return: -
 * Effects: Adds current pixel to a Pnm_ppm given by void *cl
 ************************/
void apply90(int i, int j, A2Methods_UArray2 a, void *elem, void *cl) 
{
        Pnm_ppm newPic = cl;
        const struct A2Methods_T *method = getMethod(newPic);
        int col = newPic->width - j - 1;
        Pnm_rgb newLoc = (Pnm_rgb)(method->at(newPic->pixels, col, i));
        *newLoc = *(Pnm_rgb) elem;

        (void)a;
}

/********** apply180 ********
 * 
 * Apply function used in mapping that will add each element
 *      to Pnm_ppm newpic in the specifed location when the image is rotaed
 *      180 degrees
 * 
 * Inputs: 
 *         int i: The column index of the element being processed.
 *         int j: The row index of the element being processed.
 *         A2 a: The 2D array being operated on (not used in this function).
 *         void *elem: Pointer to the source element to be copied (Pnm_rgb)
 *         void *cl: Pointer to the Pnm_ppm structure representing the 
 *                destination image.
 *
 * Return: -
 * Effects: Adds current pixel to a Pnm_ppm given by void *cl
 ************************/
void apply180(int i, int j, A2Methods_UArray2 a, void *elem, void *cl) 
{
        Pnm_ppm newPic = cl;
        const struct A2Methods_T *method = getMethod(newPic);
        int col = newPic->width - i - 1;
        int row = newPic->height - j - 1;
        Pnm_rgb newLoc = (Pnm_rgb)(method->at(newPic->pixels, col, row));
        *newLoc = *(Pnm_rgb) elem;

        (void)a;
}

/********** apply270 ********
 * 
 * Apply function used in mapping that will add each element
 *      to Pnm_ppm newpic in the specifed location when the image is rotaed
 *      270 degrees
 * 
 * Inputs: 
 *         int i: The column index of the element being processed.
 *         int j: The row index of the element being processed.
 *         A2 a: The 2D array being operated on (not used in this function).
 *         void *elem: Pointer to the source element to be copied (Pnm_rgb)
 *         void *cl: Pointer to the Pnm_ppm structure representing the
 *                destination image.
 *
 * Return: -
 * Effects: Adds current pixel to a Pnm_ppm given by void *cl
 ************************/
void apply270(int i, int j, A2Methods_UArray2 a, void *elem, void *cl) 
{
        Pnm_ppm newPic = cl;
        const struct A2Methods_T *method = getMethod(newPic);
        int row = newPic->height - i - 1;
        Pnm_rgb newLoc = (Pnm_rgb)(method->at(newPic->pixels, j, row));
        *newLoc = *(Pnm_rgb) elem;

        (void)a;
}

/********** rotate ********
 * 
 * Takes the image to be rotated, starts a timer, and prints out the 
 *       rotated image.
 * 
 * Inputs:
 *         int rotation: the degrees the image is rotated (0, 90, 180, or 270)
 *         Pnm_ppm picture: the picture to be rotated
 *         CPUTime_T timer: the time object to measure execution time
 *              
 * Return: double containing the time taken to rotate the image in nanoseconds
 * 
 * Effects:
 *     - The rotated image is printed to stdout.
 *
 ************************/
double rotate(int rotation, Pnm_ppm picture, CPUTime_T timer)
{
        const struct A2Methods_T *method = getMethod(picture);
        Pnm_ppm updated_pic;
        double time_used; 
        if (rotation == 90 || rotation == 270) {
                updated_pic = updatePicture(picture, true);
                if (rotation == 90) {
                        CPUTime_Start(timer);
                        method->map_default(picture->pixels, apply90, 
                                                updated_pic);
                        time_used = CPUTime_Stop(timer);
                } else if (rotation == 270){
                        CPUTime_Start(timer);
                        method->map_default(picture->pixels, apply270, 
                                                updated_pic);
                        time_used = CPUTime_Stop(timer);
                }
        } else if (rotation == 180){ 
                updated_pic = updatePicture(picture, false);
                CPUTime_Start(timer);
                method->map_default(picture->pixels, apply180, updated_pic);
                time_used = CPUTime_Stop(timer);
        } else if (rotation == 0) {
                CPUTime_Start(timer);
                updated_pic = picture;
                time_used = CPUTime_Stop(timer);
        }
        Pnm_ppmwrite(stdout, updated_pic);
        Pnm_ppmfree(&updated_pic);
        return time_used;
}