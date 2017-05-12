#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();
	take_picture();
	display_picture(1,500000);
	int sum = 0;
	int error;
	int nowp = 0;
	int proportional_signal = 0;
	float kp = 0.5;
	/** Location controls the col, pixelH is the variable for the horizontal pixels*/
	int location, int pixelH, int checkRed, int s;
	while(true){
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
			error = error + (location - 160) * s;
			sum = sum + (location - 160) * s;
			proportional_signal = error * kp;
			while(true){
				if (number_of_white_pixels > 0){
				v_left = 70 + proportional_signal;
				v_right = 70 - proportional_signal;
				set_motor(1, v_left);
				set_motor(2, v_right);} /** The prints for each if statement is only for testing */
				}
				else{
					v_left = 70 - proportional_signal;
					v_right = 70 + proportional_signal;
					set_motor(1, v_left);
					set_motor(2, v_right);
				}
			}
		}
	}
}

/** From the lecture, we should stick with using an array to make the robots navigation better.*/
/** To get past the split paths, we should make the code remember the previous picture it took and what happens to
that path so if it's a dead end, it can retrace its path to take the other path (but might make coding take longer)*/

