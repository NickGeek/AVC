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
};

class Camera: public Sensor {
	int whitePixels;
	int totalError;

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		this->whitePixels = 0;
		int sum = 0;
		int error = 0;
		int whiteThreshold = 0;
		ErrorSignal errorSignal = {0, 0 ,0};
		int pixelWhiteness[320] = {};

		/** PID Constants */
		float kp = 0.0009;
		float ki = 0.001;
		float kd = 0.01;

		take_picture();
		for (int i = 0; i < 320; i++) {
			pixelWhiteness[i] = get_pixel(120, i, 3);
			// printf("%d\n", pixelWhiteness[i]);
			whiteThreshold += pixelWhiteness[i];
		}
		// whiteThreshold = whiteThreshold/320;
		// printf("White threshold: %d\n", whiteThreshold);
		whiteThreshold = 80;

		for (int i = 0; i < 320; i++) {
			if(pixelWhiteness[i] > whiteThreshold) {
				whitePixels++;
				sum = 1;
			}
			else {
				sum = 0;
			}
			error = error + (i - 160) * sum;
			errorSignal.p = error * kp;

			if (i <= 310) {
				if (pixelWhiteness[i+10] > whiteThreshold) {
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
		errorSignal.i = totalError*ki;
		errorSignal.i = 0;

		return errorSignal;
	}

public:
	Movement getNextDirection() {
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement;
		if (whitePixels > 0) {
			printf("P: %d, I: %d D: %d\n", errorSignal.p, errorSignal.i, errorSignal.d);
			// printf("%d\n", errorSignal.p);
			movement.setMotor(40 - (errorSignal.p + errorSignal.i + errorSignal.d), 35 + (errorSignal.p + errorSignal.i + errorSignal.d));
		}
		else {
			// printf("Test\n");
			movement.setMotor(-40, -35);
			// movement.setMotor(0, 0);
		}

		return movement;
	}
};
