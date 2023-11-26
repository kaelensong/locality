/*
 *     timerfile.c
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

/********** open_or_fail ********
 * 
 * tests that the given file can be opened, 
 * then opens the file if possible
 * 
 * Inputs: 
 *         char *filename: the filename
 *         char *mode: the mode of reading/writing
 *              
 * Return: the pointer to the opened file
 * 
 * Notes:
 *    Will CRE if file cannot be opened
 ************************/
static FILE *open_or_fail(char *filename, char *mode) 
{
        FILE *fp = fopen(filename, mode);
        assert(fp != NULL);
        return fp;
}

/********** timerFile ********
 * 
 * Writes timing information to a file, including total time taken, 
 * the number of pixels in the picture, and time per pixel.
 * 
 * Inputs:
 *         double time_used: The total time taken in nanoseconds.
 *         char* time_file_name: The name of the file where timing 
 *         information is to be written.
 *
 * Returns: -
 *   
 * Notes:
 *      The `time_file_name` parameter must be a valid C string or NULL.
 *      Will CRE from open_or_fail if file cannot be opened
 * 
 ************************/ 
void timerFile(double time_used, char* time_file_name, Pnm_ppm picture) {
        if (time_file_name == NULL) {
                return;
        }
        
        double num_pixels = picture->width * picture->height;
        FILE *time = open_or_fail(time_file_name, "w");
        fprintf(time, "Total time taken: %.0f nanoseconds\n", time_used);
        fprintf(time, "Number of pixels: %f\n", num_pixels);
        fprintf(time, "Time per pixel:  %.0f nanoseconds\n", 
                time_used / num_pixels);
        fclose(time);   
}
