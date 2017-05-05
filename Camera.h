#include <stdio.h>
#include <time.h>
#include <string>
#include "E101.h"
#include "Sensor.h"

using namespace std;

class Camera: public Sensor {
	public:
		string getNextDirection() {
			//TODO: Get the next direction using data from the Camera
			return "";
		}
};
