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

class Camera: public Sensor {
	int whiteThreshold = 127;
	int whitePixels = 0;
	float kp = 0.5;

	int getPropSignal() {
		int sum = 0;
		int error = 0;
		int proportionalSignal = 0;
		whitePixels = 0;

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
			proportional_signal = error * kp;
		}
		return proportionalSignal;
	}

	public:
		Movement getNextDirection() {
			Movement movement = {-1, -1};
			if (whitePixels > 0) {
				int propSignal = getPropSignal();
				movement = {70 + propSignal, 70 - propSignal}
			}

			return movement;
		}
};
