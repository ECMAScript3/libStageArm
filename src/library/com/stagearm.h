#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <stdatomic.h>
//Begin returns Success
unsigned short send(unsigned char*, unsigned short);
//calibrate -- calibrates coordinate grid (redefines origin in 3D Stage)
unsigned char calibrate();//                                                    calibrate()              --Calibrates X, Y, and Z
unsigned char calibrateX();//                                                   calibrateX()             --Calibrates X
unsigned char calibrateY();//                                                   calibrateY()             --Calibrates Y
unsigned char calibrateZ();//                                                   calibrateZ()             --Calibrates Z
//moveTo -- Moves coordinate grid to position. Loses accuracy over time, suggests calibration beforehand.
unsigned char moveTo(unsigned short, unsigned short, unsigned short);//         moveTo(X, Y, Z)          --Sets stage to coords
unsigned char moveToX(unsigned short);//                                        moveTo(X)                --sets stage X to coordinate
unsigned char moveToY(unsigned short);//                                        moveTo(X)                --sets stage Y to coordinate
unsigned char moveToZ(unsigned short);//                                        moveTo(X)                --sets stage Z to coordinate
//move -- moves stage by  ammouny
unsigned char move(short, short, short);//                                      move(X, Y, Z)            --moves stage by X, Y, Z units on all axis
unsigned char moveX(short);//                                                   moveX(X)                 --moves stage by X units along X axis
unsigned char moveY(short);//                                                   moveY(Y)                 --moves stage by Y units along Y axis
unsigned char moveZ(short);//                                                   moveZ(Z)                 --moves stage by Z units along Z axis

//moveBy -- move with speed control
unsigned char moveBy(short, short, short, unsigned char);//                     move(X, Y, Z)            --moves stage by X, Y, Z units on all axis aat SPEED
unsigned char moveByX(short, unsigned char);//                                  moveByX(X, SPEED)        --moves stage by X units along X axis at SPEED
unsigned char moveByY(short, unsigned char);//                                  moveByX(Y, SPEED)        --moves stage by X units along X axis at SPEED
unsigned char moveByZ(short, unsigned char);//                                  moveByX(Z, SPEED)        --moves stage by X units along X axis at SPEED


//actuate -- Toggle vaccum pin
unsigned char actuate();//                                                      actuate()                --Toggles vaccum state (Grab->Release || Release->Grab)
unsigned char actOn();//                                                        actOn()                  --Sets vaccum pen to open state (Grab)
unsigned char actOff();//                                                       actOff()                 --sets vaccum pen to closed state (Releas)
//End Returns Success