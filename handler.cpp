#include "computer.cpp"
#include "recorder.cpp"
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
// process commands and its arguments: keyword -> argv[0], arguments ->
// argv[1,2...n]
int command_handler(int argc, std::vector<std::string> argv) {
  // list of valid commands
  const std::vector<std::string> commands = {"track", "endsession"};
  // list of available satellites
  const std::string satellites[2] = {"satl1", "satl2"};
  // check whether input is empty or not
  if (!argv.empty()) {
    // find entered command in list of available commands
    if (std::find(commands.begin(), commands.end(), argv[0]) !=
        commands.end()) {
      // if a user entered command "track" -> check arguments
      if (argv[0] == commands[0]) {
        const std::string *p;
        p = std::find(satellites, satellites + 2, argv[1]);
        // if "track" command was entered without arguments -> throw an error
        if (argc < 2) {
          std::cerr << "Usage: track <satellite[id]>\n";
        } else if (p != satellites + 2) {
          // if entered satellite is in list of satellites -> track this
          // satellite and then send this satellite with its data to
          // records_handler
          std::cout << "Tracking: " << argv[1] << "...\n";
          int latitude = latitudecal();
          int longitude = longitudecal();
          records_handler(argv[1], latitude, longitude);
        } else {
          std::cerr << argv[1] << " is not in list of available satellites\n";
        }
      } else if (argv[0] == commands[1]) {
        //"endsession" was execuded -> exit from while loop
        std::cout << "Ending session..." << std::endl;
      } // trash processing section
    } else {
      std::cerr << "Error: " << argv[0] << " is not a command\n";
    }
  } else {
    std::cerr << "Error: empty string" << std::endl;
  }
  return EXIT_SUCCESS;
}
