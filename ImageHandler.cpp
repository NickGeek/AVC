#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	take_picture();
	display_picture(1,500000);
	int sum = 0;
	/** Location controls the col, pixelH is the variable for the horizontal pixels*/
	int location, int pixelH, int checkRed, int s;
	for(location = 0, location < 320, location++){
	/** since this is only three pixels from the same line, maybe adding a vertical pixel might be good. */  
		pixelH = get_pixel(location, 120, 3);
		checkRed = get_pixel(location, 120, 0);
		if(pixelH > 127){
			s = 1;
		}
		if(checkRed ){ /** finish if statement to make it work*/
			s = -1;
		}
		else{
			s = 0;
		}
		sum = sum + (location - 160) * s;
		while(true){
			if(sum < 0){
				turn_right();
				println("Turning right"); /** The prints for each if statement is only for testing */
			}
			if(sum > 0){
				turn_left();
				println("Turning left");
			}
			if(sum = 0){
				drive_forward();
				println("Moving forward");
			}
			if(sum = -1){
				/** add code to switch to IR and turn off this camera */
				println("Red detected, switching to IR sensor");
			}
		}
	}
}

/** From the lecture, we should stick with using an array to make the robots navigation better.*/
/** To get past the split paths, we should make the code remember the previous picture it took and what happens to
that path so if it's a dead end, it can retrace its path to take the other path (but might make coding take longer)*/

