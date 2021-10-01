#define _USE_MATH_DEFINES
#include <ctime>
#include <iostream>
#include <math.h>
#include "math_lib.h"

namespace Project_Orion
{
	//earth radius
	const float RADIUS_MAJOR = 6378137.0;
	//getting a random latitude from the range of {-90; 90}, replace it with yours custom latitude&longitude stream
	float latitudecal() {
		srand((unsigned)time(0));
		float latitude;
		latitude = (rand() % 180) - 90.0;
		return latitude;
	}
	//the same with longitude but the range is {-180; 180}
	float longitudecal() {
		srand((unsigned)time(0));
		float longitude;
		longitude = (rand() % 360) - 180.0;
		return longitude;
	}
	float toRadians(float degree)
	{
		return (degree * (M_PI / 180.0));
	}
	//latitude to screen pixels {-1; 1}
	float yAxisProjection(float input) {
		return std::log(std::tan(M_PI / 4.0 + toRadians(input) / 2.0)) * RADIUS_MAJOR;
	}
	//longitude to screen pixels {-1; 1}
	float xAxisProjection(float input) {
		return RADIUS_MAJOR * toRadians(input);
	}
	//getting a random color position at the vertor of colors 
	size_t randomColor() {
		srand((unsigned)time(0));
		size_t randomIndex;
		randomIndex = rand() % 10;
		return randomIndex;
	}
}