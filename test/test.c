#include "stdio.h"
#include <stageArm.h>

int main() {
    init("/dev/cu.usbmodem1411");
    set_period(500);
    move_y(4);
    set_period(2000);
    move_y(-10);
}
