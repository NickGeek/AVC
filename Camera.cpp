#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Sensor.cpp"

using namespace std;

class Camera: public Sensor {
	int whitePixels;
	int totalError;
	int whiteThreshold;

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		this->whitePixels = 0;
		int sum = 0;
		int error = 0;
		ErrorSignal errorSignal = {0, 0 ,0};

		/** PID Constants */
		float kp = 0.0009;
		float ki = 0.001;
		float kd = 0.01;

		take_picture();
		for (int i = 0; i < 320; i++) {
			if(get_pixel(120, i, 3) > this->whiteThreshold) {
				whitePixels++;
				sum = 1;
			}
			else {
				sum = 0;
			}
			error = error + (i - 160) * sum;
			errorSignal.p = error * kp;

			if (i <= 310) {
				if (get_pixel(120, i+10, 3) > this->whiteThreshold) {
					sum = 1;
				}
				else {
					sum = 2;
				}
				int newError = error + (i - 160) * sum;
				errorSignal.d = (newError-error)*kd;
			}
		}
		this->totalError += error;
		// errorSignal.i = totalError*ki;
		errorSignal.i = 0;

		if (this->whitePixels > 300) {
			this->quadrant = 3;
		}

		return errorSignal;
	}

public:
	Camera() {
		this->whitePixels = 0;
		this->totalError = 0;
		this->whiteThreshold = 0;
	}

	Movement getNextDirection() {
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement;

		if (whitePixels > 0) {
			printf("P: %d, I: %d D: %d\n", errorSignal.p, errorSignal.i, errorSignal.d);
			movement.setMotion(errorSignal);
		}
		else {
			if (this->quadrant < 3) {
				movement.setMotion(-40, -40);
			}
			else if (this->quadrant == 3) {
				//TODO: Turn 90 degrees left
				movement.setMotor(0, 0);
			}
		}

		return movement;
	}
};
