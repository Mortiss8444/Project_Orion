#include "computer.cpp"
#include "mapmaker.cpp"
#include "recorder.h"
#include "tokenize.cpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Handler {
public:
  virtual Handler *SetNext(Handler *handler) = 0;
  virtual std::string Handle(std::string request) = 0;
};
class AbstractHandler : public Handler {
private:
  Handler *next_handler_;

public:
  AbstractHandler() : next_handler_(nullptr) {}
  Handler *SetNext(Handler *handler) override {
    this->next_handler_ = handler;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // $isEmpty->setNext($IsACommand)->...;
    return handler;
  }
  std::string Handle(std::string request) override {
    if (this->next_handler_) {
      return this->next_handler_->Handle(request);
    } // at the end, if input will not have satisfied any condition -> return
      // nothing
    return {};
  }
};
// here we check whether input is empty or not
class IsEmpty_Handler : public AbstractHandler {
public:
  std::string Handle(std::string request) override {
    if (request.empty()) {
      return "Error: empty string\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
// this class is responsible for command(vec[0]) recognition
class IsACommand_Handler : public AbstractHandler {
protected:
  vector<string> vec;
  // list of all commands
  const std::vector<std::string> commands = {"track", "endsession", "help"};

public:
  std::string Handle(std::string request) override {
    // here we split a string into command(vec[0]) and args(vec[1,2,3...n])
    vec = input_handler(request);
    // is vec[0] a command? if no -> throw an error
    if (find(commands.begin(), commands.end(), vec[0]) == commands.end()) {
      return "Error: " + vec[0] + " is not a command\n";
    } else { // if yes -> send to next handler
      return AbstractHandler::Handle(request);
    }
  }
};
// here we check everything related to "track" command
class TrackCommand_Handler : public IsACommand_Handler {
protected:
  // a vector of all satellite names
  const std::vector<std::string> satellites = {
      "NSS-9", "TDRS-10", "AMC-4", "GOES_15", "Galaxy-15", "SatMex_5"};
  std::vector<Datacell> datastorage;

public:
  std::string Handle(std::string request) override {
    // here we split a string into command(vec[0]) and args(vec[1,2,3...n])
    vec = input_handler(request);
    // is it a "track" command?
    if (vec[0] == commands[0]) {
      // what about args?
      if (vec.size() < 2) { // no args? it's sad...
        return "Usage: track <satellite[id]>\n";
      } else if (std::find(satellites.begin(), satellites.end(), vec[1]) !=
                 satellites.end()) { // is it a proper arg?
        std::cout << "Tracking: " + vec[1] + "...\n";
        double latitude = latitudecal();
        double longitude = longitudecal();
        // if satellite's name is valid -> add it to the vector and draw a map
        records_handler(datastorage, vec[1], latitude, longitude);
        map_handler(vec[1], 60, 145);
        return {};
      } else { // trash arg
        return "Error: " + vec[1] + " is not in list of available satellites\n";
      }
    } else { // if this is not a "track" command -> send to next handler
      return AbstractHandler::Handle(request);
    }
  }
};
// here we check everything related to "endsession" command
class EndSessionCommand_Handler : public IsACommand_Handler {
public:
  std::string Handle(std::string request) override {
    // here we split a string into command(vec[0]) and args(vec[1,2,3...n])
    vec = input_handler(request);
    // is it a "endsession" command
    if (vec[0] == commands[1]) {
      if (vec.size() > 1) { // any args? if yes -> it's sad...
        return "Error: 'endsession' has no arguments\n";
      } else { // is everything fine? if yse -> close session
        return "Ending session...\n";
      }
    } else { // if this is not a "endsession" command -> send to next handler
      return AbstractHandler::Handle(request);
    }
  }
};
// here we check everything related to "help" command
class HelpCommand_Handler : public TrackCommand_Handler {
protected:
  // a vector of flags related to "help" command (-c - commands, -s -
  // satellites)
  const std::vector<std::string> helpFlags = {"-c", "-s"};

public:
  std::string Handle(std::string request) override {
    // here we split a string into command(vec[0]) and args(vec[1,2,3...n])
    vec = input_handler(request);
    // is it a "help" command
    if (vec[0] == commands[2]) {
      if (vec.size() < 2) { // no args? it's sad...
        return "Usage: help <-flag>\n";
      } else if (vec[1] == helpFlags[0]) { // list of commands?
        return "List of available commands during session:\n\tendsession "
               "-> closing session\n\thelp -c -> list of all "
               "commands\n\thelp -s -> list of all satellites\n\ttrack "
               "<satl_name> -> printing sattelite's "
               "current position on world map\nList of commands "
               "available beyond session:\n\topensession -> starting "
               "session\n\tclear -> cleaning screen\n\thelp -> list of all "
               "commands\n\texit -> "
               "closing programm\n";
      } else if (vec[1] == helpFlags[1]) { // list of satellites?
        std::ostringstream os;
        std::copy(std::begin(satellites), std::end(satellites),
                  std::ostream_iterator<string>(os, " "));
        std::string result = os.str() + "\n";
        return result; // display the contents of the vector of satellite names
      } else           // trash args
        return "Error: invalid argument\n";
    } else { // if this is not a "help" command -> send to next handler
      return AbstractHandler::Handle(request);
    }
  }
};
// here we display all errors
void ClientCode(Handler &handler, string &input) {
  const std::string result = handler.Handle(input);
  std::cout << result;
}
// this guy is responsible for pointers initialization, input taking and trash
// deleting
int command_handler(std::string &input) {
  IsEmpty_Handler *empty = new IsEmpty_Handler;
  IsACommand_Handler *command = new IsACommand_Handler;
  TrackCommand_Handler *track = new TrackCommand_Handler;
  EndSessionCommand_Handler *endsession = new EndSessionCommand_Handler;
  HelpCommand_Handler *help = new HelpCommand_Handler;
  empty->SetNext(command)->SetNext(track)->SetNext(endsession)->SetNext(help);

  ClientCode(*empty, input);

  delete empty;
  delete command;
  delete track;
  delete endsession;
  delete help;
  return EXIT_SUCCESS;
}
