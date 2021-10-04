#include <iostream>

namespace Project_Orion
{
    void appearance() {
        const char* logo = R"(    
	    ____               _           __      ____       _           
	   / __ \_________    (_)__  _____/ /_    / __ \_____(_)___  ____ 
	  / /_/ / ___/ __ \  / / _ \/ ___/ __/   / / / / ___/ / __ \/ __ \
	 / ____/ /  / /_/ / / /  __/ /__/ /_    / /_/ / /  / / /_/ / / / /
	/_/   /_/   \____/_/ /\___/\___/\__/____\____/_/  /_/\____/_/ /_/ 
	                /___/             /_____/                         )";
        // well, simple logo and description...
        const std::string description =
            "This is a demo version of a program, which displays "
            "a satellite on a world map. Here is the list of available commands during session:\n"
            "\tendsession -> closing session\n"
            "\thelp -c -> list of all commands\n"
            "\thelp -s -> list of all satellites\n"
            "\ttrack <satl_name> -> prints a satellite on a world map\n"
            "\tstop <satl_name> -> removes a satellite from a world map\n";
        std::cout << logo << "\n" << description << std::endl;
    }
}

#include <vector>
#include <thread>
#include "handler.h"
#include "GLmain.h"
#include "Sat_class.h"

using namespace Project_Orion;

void mainLoop()
{
    // show logo and description
    appearance();
    std::string rawinput = "";
    const std::string terminator = { "endsession" };
    // here we check whether a user finished session or not
    while (rawinput != terminator) {
        std::cout << "> ";
        std::getline(std::cin, rawinput);
        command_handler(rawinput);
        if (std::cin.eof()) {
            terminateGL = true;
            std::cerr << "[Info]: Terminating session..." << std::endl;
            break;
        }
    }
}
int main() {
    std::thread worker0(glLoop), worker1(mainLoop);

    worker0.join();
    worker1.join();

    return EXIT_SUCCESS;
}
