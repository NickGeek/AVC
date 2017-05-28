#include <stdio.h>
#include <time.h>
#include "E101.h"

using namespace std;

class Sensor {
public:
	int quad;
	bool turning;

protected:
	int maxValue[3] = {1, 1, 1};
	int minValue = 0;

	int getRelativeValue(int sensorValue, int sensorNumber) {
		if (sensorValue > this->maxValue[sensorNumber]) this->maxValue[sensorNumber] = sensorValue;
		// if (sensorValue < this->minValue) this->minValue = sensorValue;

		//TODO: Get relative value
		int relValue = ((float)sensorValue/this->maxValue[sensorNumber])*255;
		if (relValue > 255) relValue = 255;
		return relValue;
	}
};
