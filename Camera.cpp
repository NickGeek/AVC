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

	bool straight;
		
	/** PID Constants */
	float kp = 0.001;
	float ki = 0;
	float kd = 0.001;

	/** Get current PID values */
	ErrorSignal getErrorSignal(int height) {
		this->whitePixels = 0;
		this->whiteThreshold = 120;
		int redPixels = 0;
		int sum = 0;
		int error = 0;
		ErrorSignal errorSignal = {0, 0 ,0};


		take_picture();
		for (int i = 0; i < 320; i++) {

			/** Get P value */
			int pixelValue = get_pixel(height, i, 3);
			if(pixelValue > whiteThreshold) {
				whitePixels++;
				sum = 1;
			}
			else {
				sum = 0;
			}
			int oldError = error;
			error += (i - 160) * sum;
			errorSignal.p = error * kp;

			/** Get D value */
			if (get_pixel(220, i, 3) > whiteThreshold) {
				sum = 1;
			}
			else {
				sum = 2;
			}
			int newError = oldError + (i - 160) * sum;
			errorSignal.d = (newError-error)*kd;

			/** Find out about glorious communist red pixels */
			if (get_pixel(height, i, 0) > 230) {
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
		return errorSignal;
	}

	bool shouldKeepTurning() {
		ErrorSignal errorSignal = {0, 0, 0};
		errorSignal = getErrorSignal(200);
		printf("P-Value: %d\n", errorSignal.p);
		return (errorSignal.p != 0 && this->whitePixels > 0);
	}

public:
	bool q3JustStarted;

	Camera() {
		this->quad = 1;
		this->isTurning = false;
		this->q3JustStarted = false;
	}

	Movement getNextDirection() {
		int whitePixelsLeft = 0;
		int whitePixelsRight = 0;
		bool atLeftTurn = false;
		bool atRightTurn = false;
		bool atTIntersection = false;
		this->isTurning = false;
		this->q3JustStarted = false;
		ErrorSignal errorSignal = getErrorSignal(200);
		Movement movement;
		
		if (this->quad < 3){
			if (this->whitePixels > 0) {
				movement.setMotion(errorSignal);
				if (whitePixels > 305){
					this->quad = 3;
					this->q3JustStarted = true;
				}
			} else {
				movement.setMotor(-50, -45);
			}
		} else if (this->quad == 3){
			if (this->whitePixels > 0) {
				movement.setMotion(errorSignal);
			}
			else {
				take_picture();

				for (int i = 160; i < 320; i++){
					int pixelValue = get_pixel(50, i, 3);	
					if (pixelValue > whiteThreshold) {
						whitePixelsLeft++;
					}
				}
				printf("Left: %d\n", whitePixelsLeft);
				if (whitePixelsLeft >= 100) {
					atLeftTurn = true;
				}
				for (int j = 0; j < 160; j++){
					int pixelValue = get_pixel(50, j, 3);	
					if(pixelValue > whiteThreshold) {
						whitePixelsRight++;
					}
				}
				printf("Right: %d\n", whitePixelsRight);
				if (whitePixelsRight >= 120) {
					atRightTurn = true;
				}
				if (atLeftTurn && atRightTurn){
					atTIntersection = true;
				}

				if (atTIntersection) {
					printf("At a T-Intersection\n");
					this->isTurning = true;
					movement.setMotor(0, 40);
					atLeftTurn = false;
					atRightTurn = false;
					atTIntersection = false;
				}
				else if (atRightTurn) {
					this->isTurning = true;
					errorSignal = getErrorSignal(200);
					movement.setMotor(40, 0);
					atRightTurn = false;
				}
				else if (atLeftTurn) {
					this->isTurning = true;
					errorSignal = getErrorSignal(200);
					movement.setMotor(0, 35);
					atLeftTurn = false;
				}
				else {
					movement.setMotor(-50, -45);
				}
			}				
		}
		
		return movement;
	}

	bool checkForRedLine(int height) {
		int redPixels = 0;

		take_picture();
		for (int i = 0; i < 320; i++) {
			if (get_pixel(height, i, 0) > 230) {
				redPixels++;
			}
		}

		return (redPixels > 300);
	}
};
