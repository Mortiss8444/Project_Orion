#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

class Datacell {
private:
  std::string satname;
  double satlatitude, satlongtitude;

public:
  // Parameterized constructor
  Datacell(std::string name, double x1, double y1) {
    satname = name;
    satlatitude = x1;
    satlongtitude = y1;
  }
  const std::string getName() const { return satname; }
  const double getLat() const { return satlatitude; }
  const double getLong() const { return satlongtitude; }
};
/*// since there is no possibility to output a class object in terminal with
// ordinary "<<" operator, then we should override this operator
std::ostream &operator<<(std::ostream &out, Datacell const &data) {
  out << "Satname: " << data.getName() << std::endl;
  out << "Satlat: " << data.getLat() << std::endl;
  out << "Satlong: " << data.getLong() << std::endl;
  return out;
}*/
// here we add all data related to satellite, united in one unit and stored in
// vector "satldata"
int records_handler(std::vector<Datacell> &satldata, const std::string satlname,
                    const double satlat, const double satlong) {
  if (!satldata.empty()) {
    auto match = find_if(
        satldata.begin(), satldata.end(),
        [&satlname](const Datacell &obj) { return obj.getName() == satlname; });
    if (match == satldata.end()) {
      std::cout << "New element" << std::endl;
      satldata.push_back(Datacell(satlname, satlat, satlong));
    } else {
      std::cout << "I've found this shit -> " << satlname << std::endl;
    }
  } else
    satldata.push_back(Datacell(satlname, satlat, satlong));
  /*for (Datacell unit : satldata) {
    std::cout << unit << std::endl;
    // map_handler(unit.getLat(), unit.getLong());
  }*/
  return EXIT_SUCCESS;
}
