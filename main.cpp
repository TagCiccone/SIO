#include <unistd.h>
#include <iostream>
#include <linux/input.h>
#include <fcntl.h>

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

    XBOX = 316,

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

int main() {
    int fd = open("/dev/input/TODO", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    struct input_event ev;
        
    while(read(fd, &ev, sizeof(ev))>0) {

    }

    close(fd);
    return 0;
}