// #include <stdio.h>
// #include <time.h>
// #include "E101.h"
// #include "Movement.cpp"

using namespace std;

class Camera: public Sensor {
	int whitePixels;
	int totalError;
	int whiteThreshold;
	bool atTIntersection;
	int counter;
	int whitePixelsLeft;
	int whitePixelsRight;
	bool atLeftTurn;
	bool atRightTurn;
		
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
				redPixels++;
			}
		}
		this->totalError += error;
		errorSignal.i = totalError*ki;

		if (redPixels > 300) {
			this->quad = 4;
			printf("Q4!!!\n");
			errorSignal = {0, 0, 0};
			return errorSignal;
		}

		if (whitePixels > 310) {
			if (this->quad == 3) {
				this->atTIntersection = true;
			}
			else {
				this->quad = 3;
				printf("Q3 PARTY TIME!\n");
			}
		}
		for (int l = 160; l < 320; l++){
			int pixelValue = get_pixel(120, l, 3);	
			if(pixelValue > whiteThreshold) {
				whitePixelsLeft++;
			}	
		}
		if (whitePixelsLeft>=140 && this->quad == 3){
			printf("left turn\n");
			this->atLeftTurn = true;
			counter++;
		}
		for (int r = 0; r < 160; r++){
			int pixelValue = get_pixel(120, r, 3);	
			if(pixelValue > whiteThreshold) {
				whitePixelsRight++;
			}	
		}
		if (whitePixelsRight>=140 && this->quad == 3){
			printf("right turn\n");
			this->atRightTurn = true;
		}
		return errorSignal;
	}

public:
	Camera() {
		this->quad = 1;
		this->atTIntersection = false;
		this->atRightTurn = false;
		this->atLeftTurn = false;
	}

	Movement getNextDirection() {
		bool turning;
		turning = false;
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement;

		if (this->quad == 3 && this->atTIntersection) {
			movement.setMotor(40, 0);
			this->atTIntersection = false;
			this->turning = true;
		} else if (this->atLeftTurn && counter>2){
			movement.setMotor(40, 0);
			this->atLeftTurn = false;
			this->turning = true;
		} else if (this->atRightTurn){
			movement.setMotor(0, 40);
			this->atRightTurn = false;
			this->turning = true;
		} else if (whitePixels > 0) {
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
