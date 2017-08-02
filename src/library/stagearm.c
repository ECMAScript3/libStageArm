#include "stagearm.h"



unsigned char calibrateX() {
    unsigned char res;
    res = 0x05;
};
unsigned char calibrateY() {
    unsigned char res;
    res = 0x06;
};
unsigned char calibrateZ() {
    unsigned char res;
    res = 0x07;
};
unsigned char calibrate() {
    unsigned char x = calibrateX();
    unsigned char y = calibrateY();
    unsigned char z = calibrateZ();
    if (x != 0 && y != 0 && z != 0) {
        return 1;
    } else {
        return 0;
    }
}
unsigned char moveToX(unsigned short X) {
    unsigned char res[3];
    res[0] = 0x08;
};
unsigned char moveToY(unsigned short Y) {
    unsigned char* res;
    unsigned char* reCast = (unsigned char*)&Y;
    *res = 0x09;
    *(res + 1) = *reCast;
    *(res + 2) = *(reCast + 1);
    return send(res, 3);
};
unsigned char moveToZ(unsigned short Z) {
    unsigned char res[3];
    res[0] = 0x0A;
};
unsigned char moveTo(unsigned short X, unsigned short Y, unsigned short Z) {
    unsigned char xSuccess = moveToX(X);
    unsigned char ySuccess = moveToY(Y);
    unsigned char zSuccess = moveToZ(Z);
};
unsigned char move(short X, short Y, short Z) {
    unsigned char res[7];
    res[0] = 0x09;
};
unsigned char moveX(short X) {
    return move(X, 0, 0);
};
unsigned char moveY(short Y) {

};
unsigned char moveZ(short Z) {

};
unsigned char moveBy(short X, short Y, short Z, unsigned char S) {

};
unsigned char moveByX(short X, unsigned char S) {

};
unsigned char moveByY(short Y, unsigned char S) {

};
unsigned char moveByZ(short Z, unsigned char S) {

};
unsigned char actuate() {

};
unsigned char actOn() {

};
unsigned char actOff() {

};