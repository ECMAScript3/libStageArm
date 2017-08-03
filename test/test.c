#include "stdio.h"
#include "stageArm.h"

int main() {
    init("/dev/cu.usbmodem1411");
    move(1, 0, 0);
}
