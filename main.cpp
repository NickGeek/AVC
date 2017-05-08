#include <stdio.h>
#include <time.h>
#include "E101.h"

int main() {
	init();

	int[3] pixels;
	take_picture();
	/** since this is only three pixels from the same line, maybe adding a vertical pixel might be good. */  
	pixels[0] = get_pixel(80, 120, 3);
	pixels[1] = get_pixel(160, 120, 3);
	pixels[3] = get_pixel(240, 120, 3);

	for (int i = 0; i < 3; ++i) {
		printf("%d\n", pixels[i]);
	}
	return 0;
}
