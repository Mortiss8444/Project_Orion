#include <iostream>

void appearance() {
  const char *logo = R"(    
	    ____               _           __      ____       _           
	   / __ \_________    (_)__  _____/ /_    / __ \_____(_)___  ____ 
	  / /_/ / ___/ __ \  / / _ \/ ___/ __/   / / / / ___/ / __ \/ __ \
	 / ____/ /  / /_/ / / /  __/ /__/ /_    / /_/ / /  / / /_/ / / / /
	/_/   /_/   \____/_/ /\___/\___/\__/____\____/_/  /_/\____/_/ /_/ 
	                /___/             /_____/                         )";
  // well, simple logo and description...
  const std::string description =
      "This is a demo version of a program, which allows you to analyze "
      "satellite's behavior on world map \nList of available commands during "
      "session:\n\tendsession "
      "-> closing session\n\thelp -c -> list of all "
      "commands\n\thelp -s -> list of all satellites\n\ttrack "
      "<satl_name> -> printing sattelite's "
      "current position on world map\nList of commands "
      "available beyond session:\n\topensession -> starting "
      "session\n\tclear -> cleaning screen\n\thelp -> list of all "
      "commands\n\texit -> "
      "closing programm\n";
  std::cout << logo << "\n" << description << std::endl;
}

#include "handler.cpp"
#include "recorder.h"
#include <vector>

int main() {
  // show interface
  appearance();
  static std::vector<Datacell> storage = {};
  std::string rawinput = "";
  const std::string terminator = {"endsession"};
  // here we check whether a user finished session or not
  while (rawinput != terminator) {
    std::cout << "> ";
    std::getline(std::cin, rawinput);
    command_handler(rawinput);
    if (std::cin.eof()) {
      std::cerr << "Terminating session..." << std::endl;
      break;
    }
  }
  // if you will feel something unnatural - scream
  return EXIT_SUCCESS;
}
