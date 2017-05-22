#include <stdio.h>
#include <time.h>
#include "E101.h"

using namespace std;

class Sensor {
public:
	int quad;

protected:
	int maxValue = 0;
	int minValue = 0;

	int getRelativeValue(int sensorValue) {
		if (sensorValue > maxValue) maxValue = sensorValue;
		if (sensorValue < minValue) minValue = sensorValue;

		//TODO: Get relative value
		return -1;
	}
};
