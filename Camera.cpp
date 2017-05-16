#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Sensor.cpp"
#include "Movement.cpp"

using namespace std;

struct ErrorSignal {
	int p;
	int i;
	int d;
}

class Camera: public Sensor {
	int whiteThreshold = 127;
	int whitePixels = 0;
	int totalError = 0;

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

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		int sum = 0;
		int error = 0;
		this->whitePixels = 0;
		ErrorSignal errorSignal = {0, 0 ,0};

		/** PID Constants */
		float kp = 0.5;
		float ki = 0.5;
		float kd = 0.5;

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
			errorSignal.p = error * kp;
		}
		this->totalError += error;
		errorSignal.i = totalError*ki;

		return errorSignal;
	}

public:
	Camera() {
		this->whiteThreshold = getWhiteThreshold();
	}

	Movement getNextDirection() {
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement();
		if (whitePixels > 0) {
			movement = {70 + (errorSignal.p + errorSignal.i + errorSignal.d), 70 - (errorSignal.p + errorSignal.i + errorSignal.d)}
		}
		else {
			//TODO: Reverse at different angle
		}

		return movement;
	}
};
