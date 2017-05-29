#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Sensor.cpp"

struct ErrorSignal {
	int p;
	int i;
	int d;
};

#include "Movement.cpp"
#include "Camera.cpp"
#include "IR.cpp"

class MazeSolver {
	Camera camera;
	IR ir;

	void openNetworkGate() {
		connect_to_server("130.195.6.196", 1024);
		send_to_server("Please");
		char key[24];
		receive_from_server(key);
		send_to_server(key);
		this->camera.quad = 2;
	}

	void lineDriver() {
		while (this->camera.quad < 4) {
			this->camera.getNextDirection().move();
			if (this->camera.q3JustStarted) {
				sleep1(0, 500000);
			}
			else if (this->camera.isTurning) {
				sleep1(1, 0);
			}
			else {
				sleep1(0, 50000);
			}
		}
	}

	void wallDriver() {
		while (this->camera.quad == 4) {
			this->ir.getNextDirection().move();
			if (this->ir.isTurning) {
				sleep1(2, 0);
			}
			else {
				sleep1(0, 10000);
			}

			if (this->camera.checkForRedLine(200)) {
				//Start Gate loop
				this->ir.waitForGate();
			}
		}
	}
public:
	void doMaze() {
		openNetworkGate();
		lineDriver();
		wallDriver();
	}
};

int main() {
	init();
	MazeSolver solver;
	solver.doMaze();

	return 0;
}
