class Movement {
	int motorLeft;
	int motorRight;
	int baseSpeed;

public:
	Movement() {
		this->baseSpeed = 40;
		setMotor(0, 0);
	}

	Movement(int motorLeft, int motorRight) {
		this->baseSpeed = 40;
		setMotor(motorLeft, motorRight);
	}

	void setMotor(int motorLeft, int motorRight) {
		if (motorLeft > 255) motorLeft = 254;
		if (motorRight > 255) motorRight = 254;
		if (motorLeft < -255) motorLeft = -254;
		if (motorRight < -255) motorRight = -254;

		this->motorLeft = motorLeft;
		this->motorRight = motorRight;
	}

	void setMotion(ErrorSignal errorSignal) {
		printf("test");
		setMotor(baseSpeed - (errorSignal.p + errorSignal.i + errorSignal.d), (baseSpeed - 5) + (errorSignal.p + errorSignal.i + errorSignal.d));
	}

	void move() {
		// printf("%d:%d\n", this->motorLeft*-1, this->motorRight);
		set_motor(1, this->motorLeft*-1);
		set_motor(2, this->motorRight);
	}
};
