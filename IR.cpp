using namespace std;

class IR: public Sensor {
	ErrorSignal getErrorSignal() {
		ErrorSignal errorSignal = {0, 0, 0};

		float kp = 0.035;
		int sensorFront, sensorLeft, sensorRight;

		for (int i = 0; i < 10; i++) {
			sensorFront = getRelativeValue(read_analog(0), 0);
			sensorLeft = getRelativeValue(read_analog(1), 1);
			sensorRight = getRelativeValue(read_analog(7), 2)*0.85;
			sleep1(0, 500);
		}

		// printf("F %d\n", sensorFront);
		// printf("L %d\n", sensorLeft);
		// printf("R %d\n", sensorRight);
		// printf("T: %d\n", (sensorRight - sensorLeft));
		errorSignal.p = (sensorRight - sensorLeft)*kp;
		printf("P: %d\n", errorSignal.p);

		//If we are at a wall, make a right turn
		printf("%d\n", read_analog(0));
		if (read_analog(0) > 105) {
			// printf("%d\n", read_analog(0));
			sleep1(0, 400000);
			this->isTurning = true;
		}

		return errorSignal;
	}

public:
	bool isTurning;
	IR() {
		this->isTurning = false;
	}

	Movement getNextDirection() {		
		Movement movement;
		getErrorSignal();
		if (isTurning) {
			printf("Turning\n");
			movement.setMotor(50, 35);
			this->isTurning = false;
		}
		else {
			movement.setMotion(getErrorSignal());
		}
		return movement;
	}

	void waitForGate() {
		printf("Gate has come down\n");
		int sensorFront = 0;
		bool hasComeDown = false;

		while (!hasComeDown) {
			sensorFront = getRelativeValue(read_analog(0), 0);
			if (sensorFront > 230) true;
			sleep1(0, 200000);
		}
	}
};
