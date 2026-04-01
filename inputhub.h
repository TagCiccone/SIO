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

        consumable* getConsumable(int type, int code) {
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