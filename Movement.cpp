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
		if (motorLeft > 255) motorLeft = 254;
		if (motorRight > 255) motorRight = 254;
		if (motorLeft < -255) motorLeft = -254;
		if (motorRight < -255) motorRight = -254;

		this->motorLeft = motorLeft;
		this->motorRight = motorRight;
	}

	void move() {
		// printf("%d:%d\n", this->motorLeft, this->motorRight);
		set_motor(1, this->motorLeft*-1);
		set_motor(2, this->motorRight-5);
	}
};
