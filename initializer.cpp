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

#include "handler.cpp"
#include "tokenize.cpp"
#include <vector>
/* TO DO:
 * 1. A diagram of entire project(functions, what do they do, their arguments
 * and output)
 * 2. A list of possible runtime errors which may be caused by some certain
 * function
 */
int main() {
  // show interface
  appearance();
  /* Stages of processing user's input:
   *	1. asign user's input to rawinput string, then tokenize it in
   *input_handler
   *	2. return a vector with tokenized input and asign it to "input" vector
   *	3. send "input" vector and its size as arguments to command_handler
   */
  std::string rawinput = "";
  const std::vector<std::string> terminator = {"endsession"};
  std::vector<std::string> input = {};
  // here we check whether a user finished session or not
  while (input != terminator) {
    std::cout << "> ";
    std::getline(std::cin, rawinput);
    input = input_handler(rawinput);
    command_handler(input.size(), input);
  }
  // if you will feel something unnatural - scream
  return EXIT_SUCCESS;
}
