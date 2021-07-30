#include "calculator.cpp"
#include <algorithm>
#include <stdio.h>
#include <string.h>
// a foundation for future command_handler
int command_handler(std::string &usr_input) {
  // int argc, const char **argv)
  const char *commands[] = {"track", "endsession"};
  // here we check whether a user finished session or not
  /*const std::string satellites[2] = {"satl1", "satl2"};
    std::string satlocation[2] = {};
    char name[1];
    if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << " track <satellite[id]>\n";
      return EXIT_FAILURE;
    }
    while (strcmp(argv[1], commands[1]) != 0) {
      // we simply say show this lovely sign and listen to user's commands
      std::cout << "> ";
      std::cin.getline(name, 1);
      if (strcmp(argv[1], commands[0]) == 0) {
        const std::string *p;
        p = std::find(satellites, satellites + 2, argv[2]);
        if (p != satellites + 2) {
          std::cout << "Tracking: " << argv[2] << "...\n";
          int latitude = latitudecal();
       int longitude = longitudecal();
          std::cout << "Latitude: " << latitude << "\nLongitude: " << longitude
                    << std::endl;
        } else {
          std::cerr << argv[2] << " is not in list of satellites\n";
        }

      } else if (strcmp(argv[1], commands[1]) == 0) {
        //"endsession" execuded -> exit from while loop
        std::cout << "Ending session..." << std::endl;
      }
    }*/
  while (usr_input != commands[1]) {
    std::cout << "> ";
    std::getline(std::cin, usr_input);
    if (usr_input == commands[0]) {
      // just an example of a command processing
      int latitude = latitudecal();
      int longitude = longitudecal();
      std::cout << "Latitude: " << latitude << "\nLongitude: " << longitude
                << std::endl;
    } else if (usr_input == commands[1]) {
      //"endsession" execuded -> exit from while loop
      std::cout << "Ending session..." << std::endl;
    }
    // trash processing section
    else if (usr_input.empty()) {
      std::cout << "Error: empty string" << std::endl;
    } else {
      std::cout << "Error: " << usr_input << " not a command" << std::endl;
    }
  }
  return 0;
}
