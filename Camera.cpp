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
	float kp = 0.0015;
	float ki = 0;
	float kd = 0.001;

	/** Get current PID values */
	ErrorSignal getErrorSignal() {
		this->whitePixels = 0;
		int redPixels = 0;
		int sum = 0;
		int error = 0;
		ErrorSignal errorSignal = {0, 0 ,0};
		whiteThreshold = 120;


		take_picture();
		for (int i = 0; i < 320; i++) {

			/** Get P value */
			int pixelValue = get_pixel(200, i, 3);
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

		if (whitePixels > 300) {
			if (this->quad == 3) {
				
				this->atTIntersection = true;
			}
			else {
				this->quad = 3;
				this->kp = 0.0027;
				printf("Q3 PARTY TIME!\n");
				sleep1(0, 800000);
			}
		}
		return errorSignal;
	}

public:
	Camera() {
		this->quad = 1;
	}

	Movement getNextDirection() {
		int whitePixelsLeft;
		int whitePixelsRight;
		bool atLeftTurn = false;
		bool atRightTurn = false;
		bool atTIntersection = false;
		ErrorSignal errorSignal = getErrorSignal();
		Movement movement;
		
		if (this->quad < 3){
			if (this->whitePixels > 0) {
				movement.setMotion(errorSignal);
				if (whitePixels > 300){
					this->quad = 3;
				}
			} else {
				movement.setMotor(-30, -30);
			}
		} else if (this->quad==3){
			if (this->whitePixels > 0) {
				movement.setMotion(errorSignal);
			} else {
				sleep1(1,0);
				for (int i = 160; i < 320; i++){
					int pixelValue2 = get_pixel(60, i, 3);	
					if(pixelValue2 > whiteThreshold) {
						whitePixelsLeft++;
					}	
				}
				if (whitePixelsLeft>=150{
					atLeftTurn = true;
				}
				for (int i = 0; i < 160; i++){
					int pixelValue2 = get_pixel(60, i, 3);	
					if(pixelValue2 > whiteThreshold) {
						whitePixelsRight++;
					}	
				}
				if (whitePixelsRight>=150{
					atRightTurn = true;
				}
				if (atLeftTurn && atRightTurn){
					atTIntersection = true;
				}
				if (atTIntersection){
					while (movement.setMotion(errorSignal)>3 && movement.setMotion(errorSignal)<-3){
						movement.setMotor(0, 30);
					}
					atLeftTurn = false;
					atRightTurn = false;
					atTIntersection = false;
				} else if (atRightTurn){
					while (movement.setMotion(errorSignal)>3 && movement.setMotion(errorSignal)<-3){
						movement.setMotor(30, 0);
					}
					atRightTurn = false;
				} else if (atLeftTurn){
					while (movement.setMotion(errorSignal)>3 && movement.setMotion(errorSignal)<-3){
						movement.setMotor(0, 30);
					}
					atLeftTurn = false;
				}
				    
				    
			}				
		}
		
			// printf("P: %d, I: %d D: %d\n", errorSignal.p, errorSignal.i, errorSignal.d);
			// movement.setMotor(40 - (errorSignal.p + errorSignal.i + errorSignal.d), 35 + (errorSignal.p + errorSignal.i + errorSignal.d));
			
			
		
		return movement;
	}
};
