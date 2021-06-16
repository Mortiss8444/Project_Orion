#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

class Datacell {
private:
  std::string satname;
  int satlatitude, satlongtitude;

public:
  // Parameterized constructor
  Datacell(int x1, int y1, std::string name) {
    satname = name;
    satlatitude = x1;
    satlongtitude = y1;
  }
  const std::string getName() const { return satname; }
  const int getLat() const { return satlatitude; }
  const int getLong() const { return satlongtitude; }
};
// since there is no possibility to output a class object in terminal with
// ordinary "<<" operator, then we should override this operator
std::ostream &operator<<(std::ostream &out, Datacell const &data) {
  out << "Satname: " << data.getName() << std::endl;
  out << "Satlat: " << data.getLat() << std::endl;
  out << "Satlong: " << data.getLong() << std::endl;
  return out;
}
// here we add all data related to satellite, united in one unit and stored in
// vector "satldata"
int records_handler(const std::string satlname, const int satlat,
                    const int satlong) {
  std::vector<Datacell> satldata;
  satldata.push_back(Datacell(satlat, satlong, satlname));
  for (auto unit : satldata) {
    std::cout << unit << std::endl;
  }
  return EXIT_SUCCESS;
}
