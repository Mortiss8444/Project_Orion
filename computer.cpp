#include <cstdlib>
#include <ctime>
#include <iostream>
// here is a bunch of heavy calculations
double latitudecal() {
  srand((unsigned)time(0));
  double latitude;
  latitude = (rand() % 180) - 90;
  return latitude;
}
double longitudecal() {
  srand((unsigned)time(0));
  double longitude;
  longitude = (rand() % 360) - 180;
  return longitude;
}
