#include <iostream>
#include <linux/input.h>
#include <fcntl.h>


int main() 
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