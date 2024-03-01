# locality
performs various transformations on a ppm image <br />
<br />
# Architecture
<br />
ppmtrans - checks for valid command line arguments then calls transformPic() <br />
        Holds the main function which is responsible for obtaining user inputs <br />
<br />
transform: Calls functions from modules rotate, flip, transpose and timerfile <br />
Acts as a 'secondary' main for operations and calls the needed functions <br />
<br />
rotate, flip, transpose: All three of these files interact with our other modules in the same manner as they all perform similar operations. <br />
       -Starts a timer object that was created in transform and <br />
            returns the data <br />
       -The module(s) calls updatepic in order to create a new Pnm_ppm <br />
       -Calls getmethod to receive the method and map requested by user and is stored in pnm_ppm <br />
       -These modules hide how the transformations are actually implemented and performed on the picture. <br />
<br />
updatepic: Is used by transformation functions to create a new Pnm_ppm based on the original image that is being transformed <br />
         -This modules hides interactions that go into the Pnm_ppm struct, which creates a layer of abstraction to hide image data. <br />
<br />
timerfile: Is used by transformPic() in transform to write to the file that contains information about the timer. <br />
<br />
getmethod: is used to store a helper function that all transformations need, gets the method held in the Pnm_ppm picture <br />
___ <br />
uarray2, uarray2b, A2methods <br />
<br />
-For ppmtrans, these files provide working data structures and functions for those data structures, used to store and transform the pictures <br />
-hide implementation details of the data structures themselves <br />
<br />

# Measured Performance
Computer Specs: MacBook Pro 2018, Intel(R) Core(TM) i5-8259U CPU @ 2.30GHz <br />
<br />
mobo.ppm : 8160 X 6120 <br />
 * measurements in nanoseconds * <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ <br />
               |  Row Major |  Col Major  | Block Major | <br />
━━━━━━━━━━━━━━━|━━━━━━━━━━━━|━━━━━━━━━━━━|━━━━━━━━━━━━━| <br />
Rotate 90      | 4578452005 | 4577486824  | 3579580998  | <br />
    per pixel: | 92         | 92          | 72          | <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ | <br />
Rotate 180     | 476848     | 599319      | 901104      | <br />
    per pixel: | 33         | 41          | 62          | <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━<br />
Rotate 270     | 4555193041 | 4478797652  | 3372851123  | <br />
    per pixel: | 91         | 90          | 68          | <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ | <br />

newton.ppm : 1152 X 864 <br />
 * measurements in nanoseconds * <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ <br />
               |  Row Major |  Col Major  | Block Major | <br />
━━━━━━━━━━━━━━━|━━━━━━━━━━━━|━━━━━━━━━━━━|━━━━━━━━━━━━━| <br />
Rotate 90      | 62455601   | 64887883    | 70147163    | <br />
    per pixel: | 63         | 65          | 70          | <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ <br />
Rotate 180     | 36838282   | 36453674    | 6035742     | <br />
    per pixel: | 37         | 37          | 61          | <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ | <br />
Rotate 270     | 60353206   | 60011103    | 66008684    | <br />
    per pixel: | 61         | 60          | 68          | <br />
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ <br />
<br />
It looks like for all mappings and both images, rotate 180 was by far the quickest. This could be because there is less math needed to get the new location for each pixel. <br />
<br />
Row major and column major rotations seem to be all around the same speed. This makes sense as both use plain arrays (UArray2s).<br />
<br />
For the two images we tried, the instructions per pixel were very similar for rotate 180 and for all operation using Block Major.<br />
<br />
The time per pixel remains relatively consistent across the two image sizes, especially for the same rotation angle and mapping type.<br />
<br />
Block major seemed to stay at around the same speed, no matter what size the image was, meaning that for smaller images it would be slower than row/col major for transformations but faster for block-major. This makes sense because each block is accessed as a unit so the time it takes to access a block does not necessarily depend on the size of the image.<br />
<br />

