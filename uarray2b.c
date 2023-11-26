/*
 *     uarray2b.c
 *     by Kaelen Song and Mia Taylor 
            ksong05   mtaylo16
 *     10/5/2023
 *     Homework#3
 *     summary: Implements the UArray2b ADT,
 *     which creates an 2D array using blocks
 */

#include "uarray2b.h"
#include "uarray2.h"
#include "uarray.h"
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>
#include <mem.h>
#include <stdio.h>
#include <math.h>

struct UArray2b_T {
        int U_width;
        int U_height;
        int U_size;
        int U_blocksize;
        UArray2_T array2;
};

/**********UArray2b_new********
 * Purpose: Creates/Declares a new instance of uarray2b
 * Inputs:
 *              int width: width of uarray2b instance
 *              int height: height of uarray2b instance
 *              int size: size of elements within uarray2b instance 
 *              int blocksize: the size of blocks to store elemnts within   
 * Return:  a valid instance of UArray2b_T (assume not NULL)
 * Expects: The size of an element to be greater or equal than 0
 *        Block size to be greater or equal to 0
 * NOTES: Will CRE if memory allocation fails
 ************************/
extern UArray2b_T UArray2b_new (int width, int height, int size, int blocksize)
{
        assert(blocksize >= 1 && size >= 0);
        UArray2b_T array2b;
        NEW(array2b);
        assert(array2b != NULL);
        int num_blocks_width = (width + blocksize - 1) / blocksize;
        int num_blocks_height = (height + blocksize - 1) / blocksize;
        array2b->array2 = UArray2_new(num_blocks_width, num_blocks_height, 
                            blocksize*blocksize*size);
        array2b->U_width = width;
        array2b->U_height = height;
        array2b->U_size = size;
        array2b->U_blocksize = blocksize;
        
        for (int i = 0; i < num_blocks_width; i++) {
                for (int j = 0; j < num_blocks_height; j++) {
                        UArray_T *rowp = UArray2_at(array2b->array2, i, j);
                        *rowp = UArray_new(blocksize*blocksize, size);
                }
        }
        return array2b;
}

/**********UArray2b_new_64K_block********
 * Purpose: Creates/Declares a new instance of uarray2b where the block size is
            as large as possible while still allowing a block to fit in 
            64kb of RAM.
 * Inputs:
 *              int width: width of uarray2b instance
 *              int height: height of uarray2b instance
 *              int size: size of elements within uarray2b instance   
 * Return:  a valid instance of UArray2b_T (assume not NULL)
 * Expects: The size of an element to non negative
 *        Block size to be greater or equal to 0
 * NOTES:  Will CRE if memory allocation fails
 *        If a single cell will not fit in 64KB, the block size should be 1.
 ************************/
extern UArray2b_T UArray2b_new_64K_block(int width, int height, int size)
{
        int blocksize = 0;
        assert(size >= 0);
        if (size > 64 * 1024 ) {
                blocksize = 1;
        } else {
                blocksize = sqrt( (64 * 1024 ) / size );
        }
        return UArray2b_new (width, height, size, blocksize); 
}

/**********UArray2b_free********
 * Purpose: frees memory assiacated with urray2b object
 * Inputs:
 *              UArray2b_T *array2b : the urray2b to be freed   
 * Return:  void
 * Expects: the address of array2b is not null
 *        array2b is not empty
 ************************/
extern void UArray2b_free (UArray2b_T *array2b)
{
        assert(array2b != NULL && *array2b != NULL);
        UArray2_free(&((*array2b)->array2));
        free(*array2b);
}

/**********UArray2b_width********
 * Purpose: returns the width of a urray2b object
 * Inputs:
 *        UArray2_T array2 : the urray2b to return the width of  
 * Return:  int width: the width of the array
 * Expects: array2b is a valid instance
 ************************/
extern int UArray2b_width (UArray2b_T array2b)
{
        assert(array2b != NULL);
        return array2b->U_width;
}

/**********UArray2b_height********
 * Purpose: returns the height of a urray2b object
 * Inputs:
 *              UArray2b_T array2 : the urray2b to return the height of  
 * Return:  int height: the height of the array
 * Expects: array2b is a valid instance
 ************************/
extern int UArray2b_height (UArray2b_T array2b) 
{
        assert(array2b != NULL);
        return array2b->U_height;
}

/**********UArray2b_size********
 * Purpose: returns the size of elements in array2b
 * Inputs:
 *              UArray2b_T array2b : the urray2b to return the size from  
 * Return:  int size: the size of elements within array2b
 * Expects: array2b is a valid instance
 ************************/
extern int UArray2b_size (UArray2b_T array2b)
{
        assert(array2b != NULL);
        return array2b->U_size;
}

/**********UArray2b_blocksize********
 * Purpose: returns the blocksize of elements in array2b
 * Inputs:
 *              UArray2b_T array2b : the urray2b to return the blocksize from  
 * Return:  int blocksize: the blocksize of elements within array2b
 * Expects: array2b is a valid instance
 ************************/
extern int UArray2b_blocksize(UArray2b_T array2b)
{
        assert(array2b != NULL);
        return array2b->U_blocksize;
}

/**********UArray2b_at********
 * Purpose: Will return a pointer to the postion (i, j) within array2b that
          could then be accessed by the user
 * Inputs:
 *              UArray2b_T array2b : the urray2b to return the height of 
 *              int i : the row to find
 *              int j : the height to find
 * Return:  a pointer to the address at postion (i,j) in array2b
 * Expects: array2b is a valid instance
          i and j are within the bounds of array2b
 ************************/
extern void *UArray2b_at(UArray2b_T array2b, int column, int row)
{
        assert(array2b != NULL);
        assert(column < array2b->U_width);
        assert(row < array2b->U_height );
        int col = column / array2b->U_blocksize;
        int row_b = row / array2b->U_blocksize;
        UArray_T *block = UArray2_at(array2b->array2, col, row_b);
                            
        return UArray_at(*block, array2b->U_blocksize * 
                        (column % array2b->U_blocksize) + 
                        (row % array2b->U_blocksize));
}

/**********UArray2_map_row_major********
 * Purpose: Maps the UArray2b by iterating through the blocks and visiting
 *        every cell in one block before moving to the next
 * Inputs:
 *              UArray2b_T array2b : the urray2b to iterate through
                apply : the function to be applied to each element
                void *cl : a void pointer to an extra variables or data the
                        user wants to use in the apply function
 * Return:  void
 * Expects: array2b is a valid instance
 ************************/
extern void UArray2b_map(UArray2b_T array2b, void apply(int col, int row, 
                          UArray2b_T array2b, void *elem, void *cl), void *cl) 
{
        assert(array2b != NULL);
        int num_blocks_width = (array2b->U_width + array2b->U_blocksize - 1) 
                                / array2b->U_blocksize;
        int num_blocks_height = (array2b->U_height + array2b->U_blocksize - 1) 
                                / array2b->U_blocksize;
        for (int i = 0; i < num_blocks_width; i++){
                for (int j = 0; j < num_blocks_height; j++) {
                /* gets a Uarray2(i,j) which is a block */
                        UArray_T *block = UArray2_at(array2b->array2, i, j);
                        int U_length = UArray_length(*block);
                        for (int m = 0; m < (U_length); m++) {
                                int col = i * array2b->U_blocksize + m 
                                            / array2b->U_blocksize;
                                int row = j * array2b->U_blocksize + m 
                                            % array2b->U_blocksize;
                                if (row < array2b->U_height && 
                                    col < array2b->U_width) {
                                        apply(col, row, array2b, 
                                              (UArray_at(*block, m)), cl);
                                }
                        }
                }
        }
}
