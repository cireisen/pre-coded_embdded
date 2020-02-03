#pragma once
#include <opencv2/core.hpp>
#include "GPIO.h"

using namespace cv;
Point stentext = Point(50, 100);
Point stenbtn(50, 125);
Rect stenrect(stenbtn, setsize);
Point sttext = Point(50,200);
Point stinput(50, 225);
Rect inputrect(stinput, setsize);
Point sttext2 = Point(50, 300);
Point stinput2(50, 325);
Rect input2rect(stinput2, setsize);