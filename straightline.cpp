#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
	//This sets up the RPi hardware and ensures 
	//everything is working correctly
	init();
	//Sets the motor correctly to pin 1 to rotate
	//to one direction at MAX speed
	set_motor(1,255);
	sleep(0,500000);
	//Sets the motor correctly to pin 2 to rotate
	//in the same direction where pin 1 is rotating
	set_motor(2,255);
	sleep(0,500000);
	//stops motors
	stop(1);
	stop(2);
	return 0;
}
