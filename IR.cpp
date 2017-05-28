using namespace std;

class IR: public Sensor {
	ErrorSignal getErrorSignal() {
		ErrorSignal errorSignal = {0, 0, 0};

		float kp = 0.05;
		int sensorFront, sensorLeft, sensorRight;

		for (int i = 0; i < 10; i++) {
			sensorFront = getRelativeValue(read_analog(0), 0);
			sensorLeft = getRelativeValue(read_analog(1), 1);
			sensorRight = getRelativeValue(read_analog(2), 2);
			sleep1(0, 30000);
		}

		// printf("%d\n", sensorFront);
		// printf("%d\n", sensorLeft);
		// printf("%d\n", sensorRight);
		sleep1(0, 30000);
		printf("%d\n", (sensorRight - sensorLeft));
		errorSignal.p = (sensorRight - sensorLeft)*kp;
		printf("P: %d\n", errorSignal.p);

		return errorSignal;
	}

public:
	Movement getNextDirection() {		
		Movement movement;
		getErrorSignal();
		movement.setMotion(getErrorSignal());
		return movement;
	}
};
