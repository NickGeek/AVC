#include <stdio.h>
#include <time.h>
// #include <string>
#include "libE101.so"
#include "Sensor.h"

using namespace std;

struct Movement {
	int motorLeft;
	int motorRight;
};

class Camera: public Sensor {
	int[] getImageData() {
		int[3] pixels;
		take_picture();
		/** since this is only three pixels from the same line, maybe adding a vertical pixel might be good. */  
		pixels[0] = get_pixel(80, 120, 3);
		pixels[1] = get_pixel(160, 120, 3);
		pixels[3] = get_pixel(240, 120, 3); 
	}

	double getErrorValue() {
		double error = 0;
		int numWhite = 0;

		//TODO: Calculate error

		if (numWhite > 0) {
			return error/numWhite;
		}
		else {
			return 0;
		}
	}

	public:
		Movement getNextDirection() {
			//TODO: Get the next direction using data from the Camera
			Movement movement;
			movement.motorLeft = 0;
			movement.motorRight = 0;
			return movement;
		}
};
