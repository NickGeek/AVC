#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Movement.cpp"

using namespace std;

class Sensor {
public:
	int quadrant;

	Sensor() {
		this->quadrant = 1;
	}
};
