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
  const char *description =
      R"( blahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblah
 blahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblah
 blahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblah
 1.blahblahblahblahblahblah
 2.blahblahblahblahblahblahblahblah)";
  std::cout << logo << "\n" << description << std::endl;
}
// a foundation for future command_handler
int command_handler(std::string &usr_input) {
  // here we check whether a user finished session or not
  while (usr_input != "endsession") {
    // we simply say show this lovely sign and listen to user's commands
    std::cout << "> ";
    std::cin >> usr_input;
    if (usr_input == "Input") {
      // just an example of a command processing
      std::cout << usr_input << std::endl;
    } else if (usr_input == "endsession") {
      //"endsession" execuded -> exit from while loop
      std::cout << "Ending session..." << std::endl;
    } else {
      // trash processing
      std::cout << "Error: " << usr_input << " not a command" << std::endl;
    }
  }
  // if "endsession" command was executed close command_handler
  return 0;
}

int main() {
  // show interface
  appearance();
  // run command_handler
  std::string command;
  command_handler(command);
  // if you will feel something unnatural - scream
  return 0;
}
