#include <utility>
#include <map>

#include "common.h"

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
