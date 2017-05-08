#include <stdio.h>
#include <time.h>
// #include <string>
#include "E101.h"
#include "Sensor.h"

using namespace std;

struct Movement {
	int motorLeft;
	int motorRight;
};

class Camera: public Sensor {
	double getErrorValue() {
		double error = 0;
		int numWhite = 0;

		//TODO: Calculate error

		if (numWhite > 0) {
			return error/numWhite;
		}
		else {
			return 0;
		}
	}

	public:
		Movement getNextDirection() {
			//TODO: Get the next direction using data from the Camera
			Movement movement;
			movement.motorLeft = 0;
			movement.motorRight = 0;
			return movement;
		}
};
