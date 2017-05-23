#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Sensor.cpp"
#include "Movement.cpp"

using namespace std;

class Camera: public Sensor {
	int whitePixels;
	int totalError;
	int whiteThreshold;
	int atTIntersection;

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		this->whitePixels = 0;
		int sum = 0;
		int error = 0;
		ErrorSignal errorSignal = {0, 0 ,0};

		/** PID Constants */
		float kp = 0.002;
		float ki = 0;
		float kd = 0.001;

		take_picture();
		for (int i = 0; i < 320; i++) {
			int pixelValue = get_pixel(120, i, 3);
			if(get_pixel(120, i, 3) > whiteThreshold) {
				whitePixels++;
				sum = 1;
			}
			else {
				sum = 0;
			}
			int oldError = error;
			error = error + (i - 160) * sum;
			errorSignal.p = error * kp;

			if (get_pixel(30, i, 3) > whiteThreshold) {
				sum = 1;
			}
			else {
				sum = 2;
			}
			int newError = oldError + (i - 160) * sum;
			errorSignal.d = (newError-error)*kd;
		}
		this->totalError += error;
		errorSignal.i = totalError*ki;

		if (whitePixels > 310) {
			this->quad = 3;
			this->atTIntersection = true;
			printf("Q3 PARTY TIME!\n");
		}

		return errorSignal;
	}

public:
	Camera() {
		this->quad = 1;
		this->turning = false;
		this->whiteThreshold = 110;
		this->atTIntersection = false;
	}

	Movement getNextDirection() {
		this->turning = false;
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement;

		if (this->quad == 3 && this->atTIntersection) {
			movement.setMotor(-40, 35);
			this->atTIntersection = false;
		}

		if (whitePixels > 0) {
			// printf("P: %d, I: %d D: %d\n", errorSignal.p, errorSignal.i, errorSignal.d);
			// movement.setMotor(40 - (errorSignal.p + errorSignal.i + errorSignal.d), 35 + (errorSignal.p + errorSignal.i + errorSignal.d));
			movement.setMotion(errorSignal);
		}
		else {
			movement.setMotor(-50, -45);
		}

		return movement;
	}
};
