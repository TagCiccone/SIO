#include "common.h"
#include <functional>
#include <vector>


class OutputHub {
    public:
        OutputHub(){};

        void exec();

        void addAction(action act);
    private:
        std::vector<action> actions;
};

void OutputHub::exec() {
    for (int i = 0; i < actions.size(); i++) {
        if (!actions[i].first->consumed) {
            actions[i].second(actions[i].first->value);
            actions[i].first->consumed = true;
        }
    }
}

void OutputHub::addAction(action act) {
    actions.push_back(act);
}