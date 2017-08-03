#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

typedef struct termios term_options; 
int arduino;
unsigned char init(char* serial_fd) {
    term_options t_opts;
    cfsetispeed(&t_opts, B9600);
    cfsetospeed(&t_opts, B9600);
    t_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    t_opts.c_cflag &= ~CSIZE;
    t_opts.c_cflag |= CS8;
    t_opts.c_cflag &= ~PARENB;
    t_opts.c_iflag &= ~(IXON | IXOFF | IXANY);
    t_opts.c_cflag &= ~CRTSCTS;
    t_opts.c_cc[VMIN]  = 1;
    t_opts.c_cc[VTIME] = 0;
    t_opts.c_cflag &= ~CSTOPB;
    t_opts.c_cflag |= CREAD | CLOCAL;
    t_opts.c_oflag &= ~OPOST;
    arduino = open(serial_fd, O_RDWR  | O_NONBLOCK);
    if (arduino == -1)  {
        perror("Could not connect to arduino!");
        return 1;
    }
    tcsetattr(arduino, TCSANOW, &t_opts);
    if( tcsetattr(arduino, TCSAFLUSH, &t_opts) < 0) {
        perror("Could not set terminal attributes!");
        return 1;
    }
    return 0;
};
unsigned char end() {
    return close(arduino);
};
unsigned char calibrate() {
    unsigned char k[1] = {0x00};
    write(arduino, k, 1);
    read(arduino, k, 1);
    return *k;
};
unsigned char calibrate_x() {
    unsigned char k[2] = {0x01, 0x00};
    write(arduino, k, 2);
    read(arduino, k, 1);
    return *k;
};
unsigned char calibrate_y() {
    unsigned char k[2] = {0x01, 0x01};
    write(arduino, k, 2);
    read(arduino, k, 1);
    return *k;
};
unsigned char calibrate_z() {
    unsigned char k[2] = {0x01, 0x02};
    write(arduino, k, 2);
    read(arduino, k, 1);
    return *k;
};
unsigned char move_to(float x, float y, float z) {
    unsigned char k[13];
    *k = 0x03;
    memcpy(k + 1, &x, 4);
    memcpy(k + 5, &y, 4);
    memcpy(k + 9, &z, 4);
    write(arduino, k, 13);
    read(arduino, k, 1);
    return *k;
};
unsigned char move_to_x(float x) {
    return move_to(x, 0, 0);
};
unsigned char move_to_y(float y) {
    return move_to(0, y, 0);
};
unsigned char move_to_z(float z) {
    return move_to(0, 0, z);
};
unsigned char move(float x, float y, float z) {
    unsigned char k[13];
    *k = 0x02;
    memcpy(k + 1, &x, 4);
    memcpy(k + 5, &y, 4);
    memcpy(k + 9, &z, 4);
    write(arduino, k, 13);
    read(arduino, k, 1);
    return *k;
};
unsigned char move_x(float x) {
    return move(x, 0, 0);
};
unsigned char move_y(float y) {
    return move(0, y, 0);
};
unsigned char move_z(float z) {
    return move(0, 0, z);
};
unsigned char set_period(int per) {
    unsigned char k[5];
    *k = 0x06;
    memcpy(k + 1, &per, 4);
    write(arduino, k, 5);
    read(arduino, k, 1);
    return *k;
};
unsigned char actuate() {
    unsigned char k[1] = {0x05};
    write(arduino, k, 1);
    read(arduino, k, 1);
    return *k;
};
unsigned char actOn() {
    unsigned char k[2] = {0x04, 0x01};
    write(arduino, k, 2);
    read(arduino, k, 1);
    return *k;
};
unsigned char actOff() {
    unsigned char k[2] = {0x04, 0x00};
    write(arduino, k, 2);
    read(arduino, k, 1);
    return *k;
};