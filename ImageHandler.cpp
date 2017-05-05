#include <stdio.h>
#include <time.h>
#include "E101.h"

main(){
  init();
  take_picture();
  /** since this is only three pixels from the same line, maybe adding a vertical pixel might be good. */  
  left_pixel = get_pixel(80, 120, 3);
  mid_pixel = get_pixel(160, 120, 3);
  right_pixel = get_pixel(240, 120, 3); 
}

/** From the lecture, we should stick with using an array to make the robots navigation better.*/
/** To get past the split paths, we should make the code remember the previous picture it took and what happens to
that path so if it's a dead end, it can retrace its path to take the other path (but might make coding take longer)*/
