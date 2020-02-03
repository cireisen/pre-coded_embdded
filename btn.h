#pragma once
#include <opencv2/core.hpp>

using namespace cv;

Size sz2(150, 75);
Point btn1(100, 50);
Point btn2(275, 50);
Point btn3(100, 175);
Point btn4(275, 175);
Point btn5(100, 300);
Point btn6(275, 300);
Point btnpointarray[] = { btn1,btn2,btn3,btn4,btn5,btn6 };
Rect btn1rect(btn1, sz2);
Rect btn2rect(btn2, sz2);
Rect btn3rect(btn3, sz2);	
Rect btn4rect(btn4, sz2);
Rect btn5rect(btn5, sz2);
Rect btn6rect(btn6, sz2);
Point btnleft(50, 425);
Rect btnleftrect(btnleft,Size(200,50));
Point btnRight(275, 425);
Rect btnrightrect(btnRight, Size(200, 50));
Rect btnarray[] = { btn1rect, btn2rect, btn3rect, btn4rect, btn5rect, btn6rect };
String button_strings[] = {"GPIO","EXTI","TIM","SYSTICK","",""};

