#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "Camera.cpp"

class MazeSolver {
	Camera camera;
public:
	void q1() {
		//TODO: Move in a straight line and open gate
	}

	void q2() {
		this->camera.quadrant = 2;
		while (true) {
			this->camera.getNextDirection().move();
			sleep1(0, 100000);
		}
	}

	void q3() {
		this->camera.quadrant = 3;
	}

	void q4() {
		this->camera.quadrant = 4;
	}
};

int main() {
	init();
	MazeSolver solver;
	solver.q2();

	return 0;
}
