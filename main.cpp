#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Sensor.cpp"
#include "Movement.cpp"

struct ErrorSignal {
	int p;
	int i;
	int d;
};

#include "Camera.cpp"
#include "IR.cpp"

class MazeSolver {
	Camera camera;
	IR ir;

	void openNetworkGate() {
		//TODO: Move in a straight line and open gate
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
			if (this->camera.quad == 3 && this->camera.turning) {
				sleep1(0, 500000);
			}
			else {
				sleep1(0, 100000);
			}
		}
	}

	void wallDriver() {
		while (this->camera.quad == 4) {
			this->ir.getNextDirection().move();
			sleep1(0, 100000);
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
