#include "Sat_class.h"
#include <algorithm>

namespace Project_Orion {
std::vector<Satellite::vec3> colors = {
    {1.0f, 0.8f, 0.82f},   {0.95f, 0.56f, 0.69f}, {0.81f, 0.58f, 0.85f},
    {0.3f, 0.08f, 0.55f},  {0.5f, 0.8f, 0.98f},   {0.5f, 0.87f, 0.9f},
    {0.64f, 0.83f, 0.65f}, {1.0f, 0.88f, 0.51f},  {0.73f, 0.66f, 0.64f},
    {0.7f, 0.74f, 0.77f}};
std::string Satellite::addToArray(std::vector<Satellite> &vectorOfSats,
                                  std::string &name, vec2 xy, size_t index,
                                  vec2 latlon) {
  if (!vectorOfSats.empty()) {
    auto match = find_if(
        vectorOfSats.begin(), vectorOfSats.end(),
        [&name](const Satellite &obj) { return obj.getName() == name; });
    if (match == vectorOfSats.end()) {
      vectorOfSats.push_back(Satellite(name, xy, colors[index], latlon));
      return "[Info]: Tracking: " + name + "...";
    } else {
      return "[Error]: You're already tracking satellite with this name - " +
             name;
    }
  } else {
    vectorOfSats.push_back(Satellite(name, xy, colors[index], latlon));
    return "[Info]: Tracking: " + name + "...";
  }
}
std::string Satellite::deleteFromArray(std::vector<Satellite> &vectorOfSats,
                                       std::string &name) {
  if (!vectorOfSats.empty()) {
    auto match = find_if(
        vectorOfSats.begin(), vectorOfSats.end(),
        [&name](const Satellite &obj) { return obj.getName() == name; });
    if (match != vectorOfSats.end()) {
      vectorOfSats.erase(std::remove_if(vectorOfSats.begin(),
                                        vectorOfSats.end(),
                                        [&name](const Satellite &ele) -> bool {
                                          return ele.getName() == name;
                                        }),
                         vectorOfSats.end());
      return "[Info]: The satellite - " + name +
             " has been successfully deleated";
    } else {
      return "[Error]: You're not tracking a satellite with this name - " +
             name;
    }
    return "[Error]: Undefined behaviour";
  } else {
    return "[Error]: Satellite storage is empty";
  }
}
void Satellite::displayVec(std::vector<Satellite> &vectorOfSats) {
  for (size_t i = 0; i < vectorOfSats.size(); i++) {
    std::cout << "Sat_Name: " << vectorOfSats[i].m_Stl_name << " "
              << "Pos: " << vectorOfSats[i].m_Pos.x << " "
              << vectorOfSats[i].m_Pos.y << " "
              << "Color: " << vectorOfSats[i].m_Color.r << " "
              << vectorOfSats[i].m_Color.g << " " << vectorOfSats[i].m_Color.b
              << " "
              << "Sides: " << vectorOfSats[i].m_Sides << std::endl;
  }
}
} // namespace Project_Orion
