#include "E101.h"
#include "ErrorSignal.cpp"

class Movement {
	int motorLeft;
	int motorRight;
	int baseSpeed;

public:
	Movement() {
		this->motorLeft = 0;
		this->motorRight = 0;
		this->baseSpeed = 40;
	}

	Movement(int motorLeft, int motorRight) {
		this->setMotion(motorLeft, motorRight);
	}

	void setMotion(int motorLeft, int motorRight) {
		if (motorLeft > 255) motorLeft = 255;
		if (motorRight > 255) motorRight = 255;
		if (motorLeft < -255) motorLeft = -254;
		if (motorRight < -255) motorRight = -254;

		this->setMotor(motorLeft, motorRight - 5);
	}

	void setMotion(ErrorSignal errorSignal) {
		this->setMotion(this->baseSpeed + (errorSignal.p + errorSignal.i + errorSignal.d), this->baseSpeed + (errorSignal.p + errorSignal.i + errorSignal.d));
	}

	void setMotor(int motorLeft, int motorRight) {
		this->motorLeft = motorLeft;
		this->motorRight = motorRight;
	}

	void move() {
		// printf("%d:%d\n", this->motorLeft, this->motorRight);
		set_motor(1, this->motorLeft*-1);
		set_motor(2, this->motorRight-5);
	}
};
