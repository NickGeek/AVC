#include <stdio.h>
#include <time.h>
// #include <string>
#include "libE101.so"
#include "Sensor.cpp"

using namespace std;

struct Movement {
	int motorLeft;
	int motorRight;
};

struct ErrorSignal {
	int p;
	int i;
	int d;
}

class Camera: public Sensor {
	int whiteThreshold = 127;
	int whitePixels = 0;

	/** Take every pixel visible and get the median to establish a threshold for white pixels */
	int getWhiteThreshold() {
		take_picture();

		int sum = 0;
		for (int pixelH = 0; pixelH < 320; pixelH++) {
			for (int pixelV = 0; pixelV < 240; pixelV++) {
				sum += get_pixel(pixelH, pixelV, 3);
			}
		}

		return sum/76800;
	}

	ErrorSignal getErrorSignal() {
		int sum = 0;
		int error = 0;
		float kp = 0.5;
		float ki = 0.5;
		whitePixels = 0;
		ErrorSignal errorSignal = {0, 0 ,0};

		take_picture();
		for (int location = 0; location < 320; location++) {
			int pixelH = get_pixel(location, 120, 3);
			if(pixelH > whiteThreshold) {
				whitePixels++;
				sum = 1;
			}
			else {
				sum = 0;
			}
			error = error + (location - 160) * sum;
			sum = sum + (location - 160) * sum;
			errorSignal.p = error * kp;
		}
		return proportionalSignal;
	}

	public:
		Camera() {
			whiteThreshold = getWhiteThreshold();
		}

		Movement getNextDirection() {
			Movement movement = {-1, -1};
			ErrorSignal errorSignal = getErrorSignal();
			if (whitePixels > 0) {
				movement = {70 + errorSignal.p, 70 - errorSignal.p}
			}

			return movement;
		}
};
