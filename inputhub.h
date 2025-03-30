#include <thread>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include <linux/input.h>
#include <fcntl.h>

#include <unistd.h>

#include "common.h"

int UNIVERSAL_THREAD_KILL = 0;

enum INPUT_TYPE {
    NONE = 0,
    BUTTON = 1,
    AXIS = 3
};

enum BUTTON_CODE {
    A = 304,
    B = 305,
    X = 307,
    Y = 308,
    
    LB = 310,
    RB = 311,

    L_STICK_PRESS = 317,
    R_STICK_PRESS = 318,

    XBOX_BUTTON = 316,

    WINDOW = 314,
    HAMBURGER = 315,

    SCREENSHOT = 167
};

enum AXIS_CODE {
    DPAD_VERTICAL = 17,
    DPAD_HORIZONTAL = 16,

    L_TRIGGER = 2,
    R_TRIGGER = 5,

    L_STICK_VERTICAL = 0,
    L_STICK_HORIZONTAL = 1,

    R_STICK_VERTICAL = 3,
    R_STICK_HORIZONTAL = 4
};


typedef std::pair<int, int> identifier;

struct ControllerState {
    std::map<identifier, consumable> inputs;
};

struct XboxControllerState : ControllerState {
    XboxControllerState() {
        inputs = {
            {identifier(1, 304), consumable()},
            {identifier(1, 305), consumable()},
            {identifier(1, 307), consumable()},
            {identifier(1, 308), consumable()},

            {identifier(1, 310), consumable()},
            {identifier(1, 311), consumable()},

            {identifier(1, 317), consumable()},
            {identifier(1, 318), consumable()},

            {identifier(1, 316), consumable()},

            {identifier(1, 314), consumable()},
            {identifier(1, 315), consumable()},

            {identifier(1, 167), consumable()},

            {identifier(3, 17), consumable()},
            {identifier(3, 16), consumable()},

            {identifier(3, 2), consumable()},
            {identifier(3, 5), consumable()},

            {identifier(3, 0), consumable()},
            {identifier(3, 1), consumable()},

            {identifier(3, 3), consumable()},
            {identifier(3, 4), consumable()},
        };
    };
};

enum CONTROLLER_TYPE {
    XBOX
};

class InputHub { // TODO make this a singleton
    public:
        InputHub() {
        };
        ~InputHub() {
            UNIVERSAL_THREAD_KILL = 1;
            for (int i = 0; i < events.size(); i++) {
                events[i].second.join();
            }
        };

        void makeReadThread(std::string event, CONTROLLER_TYPE controllerType);

        consumable *getConsumable(int type, int code) {
            return &(states[0].inputs.find(identifier(type,code))->second);
        }

    private:
        std::vector<std::pair<std::string, std::thread>> events;
        std::vector<ControllerState> states;
        
};

void eventReadLoop(std::string event, ControllerState *state) {
    std::string inputName = "/dev/input/" + event;

    int handle = open(inputName.c_str(), O_RDONLY);
    if (handle == -1) {
        std::cerr << "Error opening event " + event << std::endl;
        return;
    }

    struct input_event ev;

    while(!UNIVERSAL_THREAD_KILL && read(handle, &ev, sizeof(ev))>0) {
        if (ev.type == NONE) continue;
        identifier id(ev.type, ev.code);

        state->inputs[id].set(ev.value);
    }
};

void InputHub::makeReadThread(std::string event, CONTROLLER_TYPE controllerType) {
    if (controllerType == XBOX) {
        states.push_back(XboxControllerState());
    } // TODO have more/generify

    // XboxControllerState s;
    // std::thread t(eventReadLoop, event, &s);
    
    events.push_back(std::make_pair(event, std::thread(eventReadLoop, event, &states.back())));
}