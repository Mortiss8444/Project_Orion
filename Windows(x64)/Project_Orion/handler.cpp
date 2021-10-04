#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <mutex>
#include "tokenize.h"
#include "math_lib.h"
#include "handler.h"
#include "Sat_class.h"

namespace Project_Orion
{
    class Handler {
    public:
        virtual Handler* SetNext(Handler* handler) = 0;
        virtual std::vector<std::string> Handle(std::vector<std::string> request) = 0;
    };
    class AbstractHandler : public Handler {
    private:
        Handler* next_handler_;
    protected:
        std::vector<std::string> m_message;
        std::string s_message;
        std::mutex m_mtx0;
    public:
        AbstractHandler() : next_handler_(nullptr) {}
        Handler* SetNext(Handler* handler) override {
            this->next_handler_ = handler;
            // Returning a handler from here will let us link handlers in a convenient
            // way like this:
            // $isEmpty->setNext($IsACommand)->...;
            return handler;
        }
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            if (this->next_handler_) {
                return this->next_handler_->Handle(request);
            } // at the end, if an input will not have satisfied any condition -> return
              // nothing
            return {};
        }
    };
    // here we check whether input is empty or not
    class IsEmpty_Handler : public AbstractHandler {
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            if (request.empty()) {
                s_message = "[Error]: Empty string";
                m_message = input_handler(s_message);
                return m_message;
            }
            else {
                return AbstractHandler::Handle(request);
            }
        }
    };
    // this class is responsible for command(request[0]) recognition
    class IsACommand_Handler : public AbstractHandler {
    protected:
        // list of all commands
        const std::vector<std::string> m_commands = {"track", "endsession", "help", "stop"};
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            // is request[0] a command? if no -> throw an error
            if (find(m_commands.begin(), m_commands.end(), request[0]) == m_commands.end()) {
                s_message = "[Error]: " + request[0] + " is not a command";
                m_message = input_handler(s_message);
                return m_message;
            }
            else { // if yes -> send to a next handler
                return AbstractHandler::Handle(request);
            }
        }
    };
    // here we check everything related to "track" command
    class TrackCommand_Handler : public IsACommand_Handler {
    private:
        float m_pixLatitude = 0, m_pixLongitude = 0, m_latitude = 0, m_longitude = 0;
        Satellite* sat0 = nullptr;
        size_t m_colorAtIndex = 0;
    protected:
        // a vector of all satellite names, modify it for your own needs
        const std::vector<std::string> m_satellites = {
            "NSS-9", "TDRS-10", "AMC-4", "GOES_15", "Galaxy-15", "SatMex_5" };
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            // is it "track" command?
            if (request[0] == m_commands[0]) {
                // what about arguments?
                if (request.size() < 2 || request.size() > 2) { // no arguments or more than needed? it's sad...
                    s_message = "[Usage]: track <satellite[name]>";
                    m_message = input_handler(s_message);
                    delete sat0;
                    return m_message;
                }
                else if (std::find(m_satellites.begin(), m_satellites.end(), request[1]) !=
                    m_satellites.end()) { // do we have this satellite within our m_satellites vector?

                    m_latitude = latitudecal(); //getting latitude
                    m_longitude = longitudecal(); //getting longitude
                    //xAxisProjection&yAxisProjection return value is twice as big as we need, so we simply need to multiply it by 0.00000005
                    m_pixLatitude = yAxisProjection(m_latitude) * 0.00000005; //if latitude > 85 or latitude < -85 it may cause -nan(ind)
                    m_pixLongitude = xAxisProjection(m_longitude) * 0.00000005; //if longitude > 179 or longitude < -179, then pixLongitude > 1.0 and pixLongitude < -1.0 respectively
                    //pixlatitude and pixlongitude are valid only when they are within the range of [-1.0; 1.0] (including -1.0 and 1.0)
                    if ((m_pixLongitude > 1.0f || m_pixLatitude > 1.0f) || (m_pixLongitude < -1.0f || m_pixLatitude < -1.0f)) {
                        isnan(m_pixLatitude) || isnan(m_pixLongitude) ? s_message = "[Error]: Either latitude or longitude is NaN"
                            : s_message = "[Error]: Either latitude or longitude is out of range";
                        m_message = input_handler(s_message);
                    }
                    else {
                        displayInitWindow = false;
                        // if a satellite's name is valid -> add it to a vector and switch openGL to next sceen
                        m_colorAtIndex = randomColor();
                        m_mtx0.lock();
                        s_message = sat0->addToArray(satelliteStorage, request[1], { m_pixLongitude, m_pixLatitude }, m_colorAtIndex, { m_longitude , m_latitude });
                        m_message = input_handler(s_message);
                        m_mtx0.unlock();
                    }
                    delete sat0;
                    return m_message;
                } else { // trash arg
                    s_message = "[Error]: " + request[1] + " is not in list of satellites";
                    m_message = input_handler(s_message);
                    delete sat0;
                    return m_message;
                }
                delete sat0;
            }else {
                delete sat0;
                return AbstractHandler::Handle(request);
            }
        }
    };
    // here we check everything related to "endsession" command
    class EndSessionCommand_Handler : public IsACommand_Handler {
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            // is it "endsession" command
            if (request[0] == m_commands[1]) {
                if (request.size() > 1) {
                    s_message = "[Error]: 'endsession' has no arguments";
                    m_message = input_handler(s_message);
                    return m_message;
                }
                else { // is everything fine? if yse -> close session
                    s_message = "[Info]: Ending session...";
                    m_message = input_handler(s_message);
                    terminateGL = true;
                    satelliteStorage.clear();
                    colors.clear();
                    return m_message;
                }
            }else {
                return AbstractHandler::Handle(request);
            }
        }
    };
    // here we check everything related to "help" command
    class HelpCommand_Handler : public TrackCommand_Handler {
    private:
        std::ostringstream m_os;
        std::string m_result;
        // a vector of flags related to "help" command (-c = commands, -s = satellites)
        const std::vector<std::string> m_helpFlags = { "-c", "-s" };
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            // is it a "help" command
            if (request[0] == m_commands[2]) {
                if (request.size() < 2 || request.size() > 2) {
                    s_message = "[Usage]: help <-flag>";
                    m_message = input_handler(s_message);
                    return m_message;
                }
                else if (request[1] == m_helpFlags[0]) { // list of commands?
                    s_message = "List of available commands during session:\n"
                                "\tendsession -> closing session\n"
                                "\thelp -c -> list of all commands\n"
                                "\thelp -s -> list of all satellites\n"
                                "\ttrack <satl_name> -> prints a satellite on a world map\n"
                                "\tstop <satl_name> -> removes a satellite from a world map\n";
                    m_message = input_handler(s_message);
                    return m_message;
                }
                else if (request[1] == m_helpFlags[1]) { // list of satellites?
                    std::copy(std::begin(m_satellites), std::end(m_satellites),
                        std::ostream_iterator<std::string>(m_os, " "));
                    m_result = m_os.str();
                // display contents of the vector of satellite names
                    m_message = input_handler(m_result);
                    return m_message;
                }
                else {
                    s_message = "[Error]: Invalid argument";
                    m_message = input_handler(s_message);
                    return m_message;
                }
            }
            else {
                return AbstractHandler::Handle(request);
            }
        }
    };
    // here we check everything related to "stop" command
    class StopCommand_Handler : public HelpCommand_Handler {
    protected:
        Satellite* sat1 = nullptr;
    public:
        std::vector<std::string> Handle(std::vector<std::string> request) override {
            if (request[0] == m_commands[3]) {
                if (request.size() < 2 || request.size() > 2) {
                    s_message = "[Usage]: stop <satellite[name]>";
                    m_message = input_handler(s_message);
                    delete sat1;
                    return m_message;
                }else if (!request[1].empty()) {
                    if (std::find(m_satellites.begin(), m_satellites.end(), request[1]) !=
                        m_satellites.end()) {
                        m_mtx0.lock();
                        s_message = sat1->deleteFromArray(satelliteStorage, request[1]);
                        satelliteStorage.empty() ? displayInitWindow = true : displayInitWindow = false;
                        m_message = input_handler(s_message);
                        m_mtx0.unlock();
                        delete sat1;
                        return m_message;
                    }else {
                        s_message = "[Error]: Unknown satellite";
                        m_message = input_handler(s_message);
                        delete sat1;
                        return m_message;
                    }
                }else {
                    s_message = "[Error]: Undefined behaviour";
                    m_message = input_handler(s_message);
                    delete sat1;
                    return m_message;
                }
            }else {
                delete sat1;
                return AbstractHandler::Handle(request);
            }
        }
    };
    // here we display all errors
    void ClientCode(Handler& handler, std::string& input) {
        std::vector<std::string> temp = input_handler(input);
        const std::vector<std::string> result = handler.Handle(temp);
        std::string output;
        std::ostringstream stream;
        std::copy(std::begin(result), std::end(result),
        std::ostream_iterator<std::string>(stream, " "));
        output = stream.str() + "\n";
        std::cout << output;
    }
    // this guy is responsible for pointers initialization, input taking and trash
    // deleting
    int command_handler(std::string& input) {
        IsEmpty_Handler* empty = new IsEmpty_Handler;
        IsACommand_Handler* command = new IsACommand_Handler;
        TrackCommand_Handler* track = new TrackCommand_Handler;
        EndSessionCommand_Handler* endsession = new EndSessionCommand_Handler;
        HelpCommand_Handler* help = new HelpCommand_Handler;
        StopCommand_Handler* stop = new StopCommand_Handler;
        empty->SetNext(command)->SetNext(track)->SetNext(endsession)->SetNext(help)->SetNext(stop);

        ClientCode(*empty, input);

        delete empty;
        delete command;
        delete track;
        delete endsession;
        delete help;
        delete stop;
        return EXIT_SUCCESS;
    }
}
