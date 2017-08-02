

unsigned char init(char* serial_fd) {

};
unsigned char calibrate() {

};
unsigned char calibrate_x() {

};
unsigned char calibrate_y() {

};
unsigned char calibrate_z() {

};
unsigned char move_to(float x, float y, float z) {

};
unsigned char move_to_x(float x) {
    move_to(x, 0, 0);
};
unsigned char move_to_y(float y) {
    move_to(0, y, 0);
};
unsigned char move_to_z(float z) {
    move_to(0, 0, z);
};
unsigned char move(float x, float y, float z) {

};
unsigned char move_x(float x) {
    move(x, 0, 0);
};
unsigned char move_y(float y) {
    move(0, y, 0);
};
unsigned char move_z(float z) {
    move(0, 0, z);
};
unsigned char set_period(int per) {

};
unsigned char actuate() {

};
unsigned char actOn() {

};
unsigned char actOff() {

};