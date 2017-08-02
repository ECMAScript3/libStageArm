#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
//Initializes serial connection. Accepts null-terminated string for serial file descripter (eg "/dev/tty1.usb")
extern unsigned char init(char* serial_fd);
//calibrate -- calibrates coordinate grid (redefines origin in 3D Stage)
extern unsigned char calibrate();//                                                    calibrate()              --Calibrates X, Y, and Z
extern unsigned char calibrate_x();//                                                   calibrateX()             --Calibrates X
extern unsigned char calibrate_y();//                                                   calibrateY()             --Calibrates Y
extern unsigned char calibrate_z();//                                                   calibrateZ()             --Calibrates Z
//moveTo -- Moves coordinate grid to position in cm
extern unsigned char move_to(float, float, float);//                            moveTo(X, Y, Z)          --Sets stage to coords
extern unsigned char move_to_x(float);//                                        moveTo(X)                --sets stage X to coordinate
extern unsigned char move_to_y(float);//                                        moveTo(X)                --sets stage Y to coordinate
extern unsigned char move_to_z(float);//                                        moveTo(X)                --sets stage Z to coordinate
//move -- moves stage by distance in cm
extern unsigned char move(float, float, float);//                                      move(X, Y, Z)            --moves stage by X, Y, Z units on all axis
extern unsigned char move_x(float);//                                                   moveX(X)                 --moves stage by X units along X axis
extern unsigned char move_y(float);//                                                   moveY(Y)                 --moves stage by Y units along Y axis
extern unsigned char move_z(float);//                                                   moveZ(Z)                 --moves stage by Z units along Z axis

//set_period -- move with speed control
extern unsigned char set_period(float);
//actuate -- Toggle vaccum pin
extern unsigned char actuate();//                                                      actuate()                --Toggles vaccum state (Grab->Release || Release->Grab)
extern unsigned char actOn();//                                                        actOn()                  --Sets vaccum pen to open state (Grab)
extern unsigned char actOff();//                                                       actOff()                 --sets vaccum pen to closed state (Releas)
//End Returns Success