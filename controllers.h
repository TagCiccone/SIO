#include <utility>
#include <map>

#include "common.h"
#include <regex>
#include <fstream>

namespace controller {
    enum INPUT_TYPE {
        NONE = 0,
        BUTTON = 1,
        AXIS = 3
    };
}

struct ControllerState {
    std::map<identifier, consumable> inputs;
};

enum CONTROLLER_TYPE {
    XBOX,
};

std::string getEvent(CONTROLLER_TYPE controllerType) {
    std::string idStr;
    switch (controllerType) {
        case XBOX: idStr = "Xbox"; break;
    }
    std::regex pattern(R"(event(\d+))");

    std::ifstream f("/proc/bus/input/devices");

    std::string line;
    bool found_controller = false;
    std::string event;
    while (std::getline(f, line)) {
        if (!found_controller && line.find(idStr) != std::string::npos) {
            found_controller = true;
        } else if (found_controller && line.find("Handlers") != std::string::npos) {
            std::smatch matches;

            if (std::regex_search(line, matches, pattern)) {
                event = matches[1].str();
                break;
            }
        }
    } 

    f.close();

    return event;

}
