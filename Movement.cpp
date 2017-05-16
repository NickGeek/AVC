class Movement {
	int motorLeft;
	int motorRight;

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
		if (motorLeft < 0) motorLeft = 0;
		if (motorRight < 0) motorRight = 0;

		this->motorLeft = motorLeft;
		this->motorRight = motorRight;
	}

	void move() {
		set_motor(1, this->motorLeft);
		set_motor(2, this->motorRight);
	}
};
