#include <stdio.h>
#include <time.h>
#include "E101.h"

struct ErrorSignal {
	int p;
	int i;
	int d;
};

#include "Camera.cpp"

class MazeSolver {
	Camera camera;
public:
	void q1() {
		//TODO: Move in a straight line and open gate
	}

	void q2() {
		while (true) {
			this->camera.getNextDirection().move();
			if (this->camera->quad == 3) {
				sleep1(0, 500000);
			}
			else {
				sleep1(0, 100000);
			}
		}
	}

	void q3() {

	}

	void q4() {

	}
};

int main() {
	init();
	MazeSolver solver;
	solver.q2();

	return 0;
}
