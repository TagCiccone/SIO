#include "inputhub.h"
int main() {
    InputHub ihub;

    ihub.makeReadThread("event3", XBOX);

    while(true){};
    return 0;
}