#include <stdio.h>
#include <time.h>
#include "E101.h"

using namespace std;

class Sensor {
public:
	int quad;
	bool turning;

protected:
	int maxValue = 1;
	int minValue = 0;

	int getRelativeValue(int sensorValue) {
		if (sensorValue > this->maxValue) this->maxValue = sensorValue;
		if (sensorValue < this->minValue) this->minValue = sensorValue;

		//TODO: Get relative value
		int relValue = ((float)sensorValue/this->maxValue)*255;
		if (relValue > 255) relValue = 255;
		return relValue;
	}
};
