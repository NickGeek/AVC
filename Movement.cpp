#include "E101.h"
#include "ErrorSignal.cpp"

class Movement {
	int motorLeft;
	int motorRight;
	int baseSpeed = 40;

public:
	Movement() {
		this->motorLeft = 0;
		this->motorRight = 0;
	}

	Movement(int motorLeft, int motorRight) {
		this->setMotor(motorLeft, motorRight);
	}

	void setMotor(int motorLeft, int motorRight) {
		if (motorLeft > 255) motorLeft = 255;
		if (motorRight > 255) motorRight = 255;
		if (motorLeft < -255) motorLeft = -254;
		if (motorRight < -255) motorRight = -254;

		this->motorLeft = baseSpeed - motorLeft;
		this->motorRight = (baseSpeed - 5) + motorRight;
	}

	void setMotor(ErrorSignal errorSignal) {
		this->setMotor((errorSignal.p + errorSignal.i + errorSignal.d), (errorSignal.p + errorSignal.i + errorSignal.d));
	}

	void move() {
		// printf("%d:%d\n", this->motorLeft, this->motorRight);
		set_motor(1, this->motorLeft*-1);
		set_motor(2, this->motorRight-5);
	}
};
