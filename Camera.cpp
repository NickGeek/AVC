// #include <stdio.h>
// #include <time.h>
// #include "E101.h"
#include "Movement.cpp"

using namespace std;

class Camera: public Sensor {
	int whitePixels;
	int totalError;
	int whiteThreshold;
	int atTIntersection;
		
	/** PID Constants */
	float kp = 0.001;
	float ki = 0;
	float kd = 0.001;

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		this->whitePixels = 0;
		int redPixels = 0;
		int sum = 0;
		int error = 0;
		ErrorSignal errorSignal = {0, 0 ,0};


		take_picture();
		for (int i = 0; i < 320; i++) {

			/** Get P value */
			int pixelValue = get_pixel(120, i, 3);
			if(pixelValue > whiteThreshold) {
				whitePixels++;
				sum = 1;
			}
			else {
				sum = 0;
			}
			int oldError = error;
			error = error + (i - 160) * sum;
			errorSignal.p = error * kp;

			/** Get D value */
			if (get_pixel(30, i, 3) > whiteThreshold) {
				sum = 1;
			}
			else {
				sum = 2;
			}
			int newError = oldError + (i - 160) * sum;
			errorSignal.d = (newError-error)*kd;

			/** Find out about glorious communist red pixels */
			if (get_pixel(120, i, 0) > 230) {
				this->quad = 4;
				printf("Q4!!!\n");
				errorSignal = {0, 0, 0};
				return errorSignal;
			}
		}
		this->totalError += error;
		errorSignal.i = totalError*ki;

		if (whitePixels > 310) {
			if (this->quad == 3) {
				this->atTIntersection = true;
			}
			else {
				this->quad = 3;
				kp = 0.002;
				printf("Q3 PARTY TIME!\n");
			}
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
