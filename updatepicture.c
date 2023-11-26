/*
 *     updatepicture.c
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework #3
 *     summary: implements the methods for updatepicture.h which will creates 
 *              and update a Pnm_ppm picture, either by flipping it or 
 *              leaving it unchanged, and returns the updated picture.
 */


#include "updatepicture.h"
#include "getmethod.h"
#include <mem.h>

/********** updatePicture ********
 * 
 * Creates and updates a Pnm_ppm picture, either by flipping it or 
 * leaving it unchanged, and returns the updated picture.
 * 
 * Inputs: 
 *         Pnm_ppm picture The input Pnm_ppm picture to be updated.
 *         bool: is_flipped A boolean value indicating whether to 
 *                  flip the picture.
 *              
 * Return: An updated Pnm_ppm picture with the specified modifications.
 * 
 * Effects:
 *    If `is_flipped` is true, the returned picture's dimensions are swapped,
 *       and its pixel data is horizontally flipped.
 *    If `is_flipped` is false, the returned picture remains unchanged.
 ************************/
Pnm_ppm updatePicture(Pnm_ppm picture, bool is_flipped) 
{
        Pnm_ppm updated_pic;
        NEW(updated_pic);
        assert(updated_pic != NULL);
        updated_pic->denominator = picture->denominator;
        const struct A2Methods_T *method = getMethod(picture);
        updated_pic->methods = picture->methods;

        if (is_flipped) {
                updated_pic->pixels = method->new(picture->height, 
                                            picture->width, 
                                            sizeof(struct Pnm_rgb));
                updated_pic->width = picture->height;
                updated_pic->height = picture->width;
        } else {     
                updated_pic->pixels = method->new(picture->width, 
                                            picture->height, 
                                            sizeof(struct Pnm_rgb));
                updated_pic->width = picture->width;
                updated_pic->height = picture->height;
        }
        
        assert(updated_pic->pixels != NULL);
        return updated_pic;
}