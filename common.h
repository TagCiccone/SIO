#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <functional>

struct consumable {
    consumable(): value(0), consumed(0) {};

    void set(int val) {
        consumed = consumed && (value == val);
        value = val;
    }

    int32_t value;
    bool consumed;
};

typedef std::pair <consumable*, std::function<void(int)> > action;

#endif