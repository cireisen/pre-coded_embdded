#pragma once
#include <opencv2/core.hpp>

using namespace cv;

Size setsize(35,35);
Size inside(33, 33);
Point port1(25, 200);
Point port2(60, 200);
Point port3(95, 200);
Point port4(130, 200);
Point port5(165, 200);
Point gpio1(25, 400);
Point gpio2(60, 400);
Point gpio3(95, 400);
Point gpio4(130, 400);
Point gpio5(165, 400);
Point gpio6(200, 400);
Point gpio7(235, 400);
Point gpio8(270, 400);
Point gpio9(305, 400);
Point gpio10(340, 400);
Point gpio11(375, 400);
Point gpio12(410, 400);
Point port_point_array[] = { port1,port2,port3,port4,port5 };
Point gpiopointarray[] = { gpio1,gpio2,gpio3,gpio4,gpio5,gpio6,gpio7,gpio8,gpio9,gpio10,gpio11,gpio12 };
Rect gpio1rect(gpio1, setsize);
Rect gpio2rect(gpio2, setsize);
Rect gpio3rect(gpio3, setsize);
Rect gpio4rect(gpio4, setsize);
Rect gpio5rect(gpio5, setsize);
Rect gpio6rect(gpio6, setsize);
Rect gpio7rect(gpio7, setsize);
Rect gpio8rect(gpio8, setsize);
Rect gpio9rect(gpio9, setsize);
Rect gpio10rect(gpio10, setsize);
Rect gpio11rect(gpio11, setsize);
Rect gpio12rect(gpio12, setsize);
Rect port1rect(port1, setsize);
Rect port2rect(port2, setsize);
Rect port3rect(port3, setsize);
Rect port4rect(port4, setsize);
Rect port5rect(port5, setsize);
Rect portarray[] = { port1rect,port2rect, port3rect, port4rect,port5rect };
Rect gpioarray[] = { gpio1rect, gpio2rect, gpio3rect, gpio4rect, gpio5rect, gpio6rect, gpio7rect, gpio8rect, gpio9rect, gpio10rect, gpio11rect, gpio12rect };
String gpionum_string[] = {"1","2","3","4","5","6","7","8","9","10","11","12"};
String port_strings[] = { "A","B","C","D","E" };
char charportstring[] = { 'A','B','C','D','E' };
