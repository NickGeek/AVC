#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Sensor.cpp"
#include "Movement.cpp"

using namespace std;

class Camera: public Sensor {
	int whitePixels;
	int totalError;
	int turnCount;
	char turnType;
	int whiteThreshold = 110;

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		this->whitePixels = 0;
		int sum = 0;
		int error = 0;
		ErrorSignal errorSignal = {0, 0 ,0};
		int leftWhiteCount = 0;
		int rightWhiteCount = 0;
		int diffPixels = 0;


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

				if (i <= 160) leftWhiteCount++;
				if (i > 160) rightWhiteCount++;

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
		diffPixels = leftWhiteCount - rightWhiteCount; //If -ve right-heavy, if +ve left heavy

		// printf("%d\n", diffPixels);
		// if (diffPixels > 150) {
		// 	this->turnType = 'L';
		// }
		// else if (diffPixels < -150) {
		// 	this->turnType = 'R';
		// }
		// else {
		// 	this->turnType = 'P';
		// }

		// if (this->whitePixels > 310) {
		// 	printf("Q3 TIME!!!!!\n");
		// 	this->quad = 3;
		// }

		return errorSignal;
	}

public:
	Camera() {
		this->quad = 1;
		this->turning = false;
		this->turnCount = 0;
		// this->isAtJunction = false;
	}

	Movement getNextDirection() {
		this->turning = false;
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement;
		// printf("%d\n", whitePixels);
		// if (this->quad == 3) {
		// 	switch (this->turnType) {
		// 		case 'L':
		// 			movement.setMotor(-40, 35);
		// 			return movement;
		// 			break;

		// 		case 'R':
		// 			movement.setMotor(40, -35);
		// 			return movement;
		// 			break;
		// 	}
		// }

		if (whitePixels > 0) {
			// printf("P: %d, I: %d D: %d\n", errorSignal.p, errorSignal.i, errorSignal.d);
			// movement.setMotor(40 - (errorSignal.p + errorSignal.i + errorSignal.d), 35 + (errorSignal.p + errorSignal.i + errorSignal.d));
			movement.setMotion(errorSignal);
		}
		// else if (this->quad == 3) {
			

		// 	this->turnType = 'P';
		// 	this->turnCount++;
		// 	this->turning = true;
			
		// }
		else {
			movement.setMotor(-50, -45);
		}

		return movement;
	}
};
