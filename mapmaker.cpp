#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <tgmath.h>
#include <thread>
#include <vector>
void map_handler(std::string, double, double);
std::string getFileContents(std::ifstream &);
void draw(std::string &, int, std::string &);

void map_handler(std::string inpSatlName, double inpLat, double inpLong) {
  std::ifstream f("example.txt");
  std::string buffer = getFileContents(f);
  f.close();
  double factorLat = 31.0 / 180.0;
  double factorLong = 122.0 / 360.0;
  std::string line;
  std::string map;
  for (int i = 1; std::getline(std::cin, line); i++) {
    if (line == "stop")
      break;
    map += buffer;
    double x = 122.0 * (180.0 + inpLat) / 360.0;
    double y = 31.0 * (90.0 - inpLong) / 180.0;
    double rawLocalValue = x * y; //+ (double)std::log2(i);
    int localValue = std::round(rawLocalValue);

    draw(map, localValue, inpSatlName);
    std::cout << map << std::endl;
    std::cout << inpSatlName << " is at ->\t"
              << "Initial latitude: " << inpLat
              << "\tInitial longitude: " << inpLong
              << "\tSpeed: " << (double)std::log2(i) << " " << localValue
              << std::endl;

    std::cout << "Press enter and, after 5 seconds, tracking will continue "
                 "or type 'stop' to terminate tracking..."
              << std::endl;
    map.clear();
    std::chrono::seconds dura(5);
    std::this_thread::sleep_for(dura);
  }
}
std::string getFileContents(std::ifstream &File) {
  std::string Lines = ""; // All lines
  if (File)               // Check if everything is good
  {
    while (!File.eof()) {
      std::string TempLine;         // Temp line
      std::getline(File, TempLine); // Get temp line
      TempLine += "\n";             // Add newline character
      Lines += TempLine;            // Add newline
    }
    return Lines;
  } else // Return error
  {
    return "Error: Can't find file with map";
  }
}
void draw(std::string &data, int inputPos, std::string &satlName) {
  for (size_t initPos = 0; initPos < data.size(); initPos++) {
    if (initPos == inputPos) {
      div_t halfNameSize = div(satlName.size(), 2);
      int topRow = 244 - halfNameSize.quot;
      int bottomRow = 244 + halfNameSize.quot;
      int aboveSignRow = 122 + halfNameSize.quot;
      int upperLim = 244 + halfNameSize.quot + 1;
      int lowerLim = 244 - halfNameSize.quot - 1;
      int belowSignRowLim = 122 - halfNameSize.quot - 1;
      int aboveSignRowLim = 122 + halfNameSize.quot + 1;
      int belowSignRow = 122 - halfNameSize.quot;
      int signRow = halfNameSize.quot + 1;
      /*Out_of_range checking*/
      if (inputPos - lowerLim > 0 && inputPos + upperLim < data.size()) {
        /*upper and lower bounds of satellite window*/
        data.replace(initPos + belowSignRow, satlName.size(),
                     std::string(satlName.size(), '-'));
        data.replace(initPos - bottomRow, satlName.size(),
                     std::string(satlName.size(), '-'));
        /**************************************/
        /*satellite sign section*/
        data.replace(initPos, 1, ".");
        data.replace(initPos + 1, 1, "-");
        data.replace(initPos - 1, 1, "-");
        /*************************/
        /*satellite name*/
        data.replace(initPos - aboveSignRow, satlName.size(), satlName);
        /************************************/
        /*left bound of satellite window*/
        data.replace(initPos - upperLim, 1, "[");
        data.replace(initPos - aboveSignRowLim, 1, "[");
        data.replace(initPos - signRow, 1, "[");
        data.replace(initPos + belowSignRowLim, 1, "[");
        /*checking whether satellite name has even or odd amount of chars*/
        /*right bound of satellite window*/
        if (satlName.size() % 2 == 0) {
          data.replace(initPos - topRow, 1, "]");
          data.replace(initPos - belowSignRow, 1, "]");
          data.replace(initPos + halfNameSize.quot, 1, "]");
          data.replace(initPos + aboveSignRow, 1, "]");
          /*************************************/
        } else {
          data.replace(initPos + aboveSignRowLim, 1, "]");
          data.replace(initPos + signRow, 1, "]");
          data.replace(initPos - belowSignRowLim, 1, "]");
          data.replace(initPos - lowerLim, 1, "]");
        }
        /**********************************/
      }
    }
  }
}
