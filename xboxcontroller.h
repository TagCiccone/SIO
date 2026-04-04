#include "controllers.h"

namespace xbox
{
    const axis_input_threshold = 0.025;

    enum INPUT_CODE {
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

        SCREENSHOT = 167,

        DPAD_VERTICAL = 17,
        DPAD_HORIZONTAL = 16,

        L_TRIGGER = 2,
        R_TRIGGER = 5,

        L_STICK_VERTICAL = 0,
        L_STICK_HORIZONTAL = 1,

        R_STICK_VERTICAL = 3,
        R_STICK_HORIZONTAL = 4
    };

    struct XboxControllerState : ControllerState {
        XboxControllerState() {
            inputs = {
                {identifier(controller::BUTTON, A), consumable()},
                {identifier(controller::BUTTON, B), consumable()},
                {identifier(controller::BUTTON, X), consumable()},
                {identifier(controller::BUTTON, Y), consumable()},

                {identifier(controller::BUTTON, LB), consumable()},
                {identifier(controller::BUTTON, RB), consumable()},

                {identifier(controller::BUTTON, L_STICK_PRESS), consumable()},
                {identifier(controller::BUTTON, R_STICK_PRESS), consumable()},

                {identifier(controller::BUTTON, XBOX_BUTTON), consumable()},

                {identifier(controller::BUTTON, WINDOW), consumable()},
                {identifier(controller::BUTTON, HAMBURGER), consumable()},

                {identifier(controller::BUTTON, SCREENSHOT), consumable()},

                {identifier(controller::AXIS, DPAD_VERTICAL), consumable()},
                {identifier(controller::AXIS, DPAD_HORIZONTAL), consumable()},

                {identifier(controller::AXIS, L_TRIGGER), consumable()},
                {identifier(controller::AXIS, R_TRIGGER), consumable()},

                {identifier(controller::AXIS, L_STICK_VERTICAL), consumable()},
                {identifier(controller::AXIS, L_STICK_HORIZONTAL), consumable()},

                {identifier(controller::AXIS, R_STICK_VERTICAL), consumable()},
                {identifier(controller::AXIS, R_STICK_HORIZONTAL), consumable()},
            };
        };
    };
}