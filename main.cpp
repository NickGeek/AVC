#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();

	Camera camera;
	while (true) {
		Movement m = getNextDirection();
		set_motor(1, m.motorLeft);
		set_motor(2, m.motorRight);
		sleep1(0, 500)
	}

	return 0;
}
