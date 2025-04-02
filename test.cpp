#include "inputhub.h"
#include "outputhub.h"

void foo(int a) {
    if (a)
        std::cout << "ooooh i'm doing the thing!!!!" << std::endl;
}

int main() {
    InputHub ihub;
    OutputHub ohub;

    ihub.makeReadThread("event3", XBOX);

    ohub.addAction(
        action(
            ihub.getConsumable(1, 304),
            foo
        )
    );

    std::cout << "starting..." << std::endl;
    while(true){
        ohub.exec();
    };
    return 0;
}