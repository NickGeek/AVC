using namespace std;

class IR: public Sensor {
	char turnType = '0';
	bool reverse = false;

	ErrorSignal getErrorSignal() {
		ErrorSignal errorSignal = {0, 0, 0};

		float kp = 0.05;
		// kp = 0;
		int sensorFront, sensorLeft, sensorRight;

		// for (int i = 0; i < 3; i++) {
		// 	sleep1(0, 500);
		// }
		sensorFront = getRelativeValue(read_analog(0), 0);
		sensorLeft = getRelativeValue(read_analog(1), 1);
		sensorRight = getRelativeValue(read_analog(7), 2)*0.8;

		// printf("F %d\n", sensorFront);
		// printf("L %d\n", sensorLeft);
		// printf("R %d\n", sensorRight);
		// printf("T: %d\n", (sensorRight - sensorLeft));
		errorSignal.p = (sensorRight - sensorLeft)*kp;
		printf("P: %d\n", errorSignal.p);

		//If we are at a wall, make a right turn
		printf("%d and %d\n", read_analog(0), sensorRight);
		if (sensorRight < 100 && read_analog(0) > 300) {
			// printf("%d\n", read_analog(0));
			// sleep1(0, 100000);
			this->isTurning = true;
			this->turnType = 'R';
		}
		else if (sensorLeft < 100 && read_analog(0) > 400) {
			this->isTurning = true;
			this->turnType = 'L';
		}
		else if (read_analog(0) > 300) {
			this->reverse = true;
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
		// movement.setBaseSpeed(30);
		getErrorSignal();
		if (isTurning) {
			printf("Turning\n");
			if (this->turnType == 'R') {
				movement.setMotor(85, -30);
			}
			else if (this->turnType == 'L') {
				movement.setMotor(-30, 100);
			}
			this->isTurning = false;
		}
		else if (this->reverse) {
			this->reverse = false;
			movement.setMotor(-55, -35);
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
