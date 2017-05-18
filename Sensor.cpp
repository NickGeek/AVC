#include <stdio.h>
#include <time.h>
#include "E101.h"

using namespace std;

class Sensor {
protected:
	int maxValue;
	int minValue;

	int getRelativeValue(int sensorValue) {
		if (sensorValue > maxValue) maxValue = sensorValue;
		if (sensorValue < minValue) minValue = sensorValue;

		//TODO: Get relative value
		return -1;
	}

public:
	Sensor() {
		this->minValue = 0;
		this->maxValue = 0;
	}
};
