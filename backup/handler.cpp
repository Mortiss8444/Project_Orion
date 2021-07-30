#include "computer.cpp"
#include "recorder.h"
#include "test.cpp"
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
// process commands and its arguments: keyword -> argv[0], arguments ->
// argv[1,2...n]
int command_handler(int argc, std::vector<std::string> argv,
                    std::vector<Datacell> &datastorage) {
  // list of valid commands
  const std::vector<std::string> commands = {"track", "endsession", "help"};
  // list of available satellites
  const std::string satellites[6] = {"NSS-9",   "TDRS-10",   "AMC-4",
                                     "GOES 15", "Galaxy-15", "SatMex 5"};
  const std::vector<std::string> helpFlags = {"-c", "-s"};
  // check whether input is empty or not
  if (argv.empty())
    std::cerr << "Error: empty string" << std::endl;
  // find entered command in list of available commands
  if (std::find(commands.begin(), commands.end(), argv[0]) == commands.end())
    std::cerr << "Error: " << argv[0] << " is not a command\n";

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
      double latitude = latitudecal();
      double longitude = longitudecal();
      records_handler(datastorage, argv[1], latitude, longitude);
      map_handler(argv[1], latitude, longitude);
    } else {
      std::cerr << argv[1] << " is not in list of available satellites\n";
    }
  } else if (argv[0] == commands[1]) {
    //"endsession" was execuded -> exit from while loop
    std::cout << "Ending session..." << std::endl;
  } else if (argv[0] == commands[2]) {
    if (argc < 2) {
      std::cerr << "Usage: help <flag>\n";
    } else if (argv[1] == helpFlags[0]) {
      std::cout << "List of available commands during session:\n\tendsession "
                   "-> closing session\n\thelp -> list of all available "
                   "commands\n\ttrack [satl_name] -> printing sattelite's "
                   "current position on world map\nList of available "
                   "commands beyond session:\n\topensession -> starting "
                   "session\n\tclear -> cleaning screen\n\thelp -> list of "
                   "all available commands\n\texit -> closing session\n"
                << std::endl;
    }
  }
  // trash processing section
  return EXIT_SUCCESS;
}
