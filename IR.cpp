using namespace std;

class IR: public Sensor {
	ErrorSignal getErrorSignal() {
		ErrorSignal errorSignal = {0, 0, 0};

		int kp = 0.1;

		for (int i = 0; i < 200; i++) {
			int sensorFront = getRelativeValue(read_analog(0));
			int sensorLeft = getRelativeValue(read_analog(1));
			int sensorRight = getRelativeValue(read_analog(7));
			sleep1(0, 300);
		}

		errorSignal.p = (sensorRight - sensorLeft)*kp;
	}

public:
	Movement getNextDirection() {		
		Movement movement;
		movement.setMotion(getErrorSignal());
	}
};
