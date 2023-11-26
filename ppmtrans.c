/*
 *     ppmtrans.c
 *     by Kaelen Song and Mia Taylor and CS40 staff
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"
#include "transform.h"

#define SET_METHODS(METHODS, MAP, WHAT) do {                    \
        methods = (METHODS);                                    \
        assert(methods != NULL);                                \
        map = methods->MAP;                                     \
        if (map == NULL) {                                      \
                fprintf(stderr, "%s does not support "          \
                                WHAT "mapping\n",               \
                                argv[0]);                       \
                exit(1);                                        \
        }                                                       \
} while (false)
static FILE *open_or_fail(char *filename, char *mode);

static void
usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle> or -flip <direction> "
                        "or transpose] [-{row,col,block}-major] "
                        "[-time timefile] [filename]\n", progname);
        exit(1);
}

int main(int argc, char *argv[]) 
{
        char *time_file_name = NULL;
        int   rotation       = 0;
        int   direction      = 0;
        int   i;
        (void) time_file_name;
        int operation = 1;
        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods);

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-row-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_row_major, 
                                    "row-major");
                } else if (strcmp(argv[i], "-col-major") == 0) {
                        SET_METHODS(uarray2_methods_plain, map_col_major, 
                                    "column-major");
                } else if (strcmp(argv[i], "-block-major") == 0) {
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                } else if (strcmp(argv[i], "-rotate") == 0) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        operation = 1;
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90 ||
                            rotation == 180 || rotation == 270)) {
                                fprintf(stderr, 
                                        "Rotation must be 0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                } else if (strcmp(argv[i], "-flip") == 0) {
                        if (!(i + 1 < argc)) {      /* no flip direction */
                                usage(argv[0]);
                        }
                        operation = 2;
                        char *dir = argv[++i];
                        if (strcmp(dir, "horizontal") == 0) {
                                direction = 0;
                        } else if (strcmp(dir, "vertical") == 0) {
                                direction = 1;
                        } else {
                             fprintf(stderr, 
                                        "Flip direction must be"
                                        "horizontal or vertical\n");
                                usage(argv[0]);   
                        }
                } else if (strcmp(argv[i], "-transpose") == 0) {
                        operation = 3; 
                } else if (strcmp(argv[i], "-time") == 0) {
                        time_file_name = argv[++i];
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                                argv[i]);
                        usage(argv[0]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else {
                        break;
                }
        }
        if (i == argc) {
                transformPic(operation, stdin, rotation, direction, 
                        time_file_name, methods);
        } else {
                FILE *file = open_or_fail(argv[i], "r");
                transformPic(operation, file, rotation, direction, 
                                time_file_name, methods);
        }
       return EXIT_SUCCESS;
}

/********** open_or_fail ********
 * 
 * tests that the given file can be opened, 
 * then opens the file if possible
 * Inputs: 
 *         char *filename: the filename
 *         char *mode: 
 *              
 * Return: the pointer to the opened file
 * 
 * Notes:
 *    Will exit failure if file cant be opened
 *    User will need to manually close the file
 ************************/
static FILE *open_or_fail(char *filename, char *mode) 
{
        FILE *fp = fopen(filename, mode);
        if(fp == NULL){
                int rc = errno;
                fprintf(stderr, "Could not open file %s with mode %s\n",
                        filename, mode);
                exit(rc);
        }
        return fp;
} 