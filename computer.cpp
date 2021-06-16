#include <cstdlib>
#include <ctime>
#include <iostream>
// here is a bunch of heavy calculations
int latitudecal() {
  srand((unsigned)time(0));
  int latitude;
  for (int index = 0; index < 1; index++) {
    latitude = (rand() % 180) - 90;
  }
  return latitude;
}
int longitudecal() {
  srand((unsigned)time(0));
  int longitude;
  for (int index = 0; index < 1; index++) {
    longitude = (rand() % 360) - 180;
  }
  return longitude;
}
