#include <opencv2/opencv.hpp>
#include "btn.h"
#include "GPIO.h"
#include "selects.h"
#include "systick.h"
#include "exti.h"
using namespace std;
void makecode();
void make_interface();
void onMouse(int, int, int, int, void *);
void guiMouse(int, int, int, int, int, void *);
void change_gui(int);
Point_<int> pt1(160, 200);
Point pt2(160, 300);
Size sz1(180, 70);
Rect rect1(pt1, sz1);
Rect rect2(pt2, sz1);
Scalar white = Scalar(255, 255, 255);
Scalar black = Scalar(0, 0, 0);
Mat image(500, 500, CV_8UC3, white);
Mat guiimage(500, 500, CV_8UC3, white);
int page = 1;
int gui = 0;
int port = 0;
int main() {
	// Point_객체 선언 
	cv::rectangle(image, rect1, black , 2);
	cv::rectangle(image, rect2, black, 2);
	putText(image, "pre-coded", Point(50, 50), FONT_HERSHEY_PLAIN, 5.0, black, 2);
	putText(image, "imbe", Point(50, 120), FONT_HERSHEY_PLAIN, 5.0, black, 2);
	putText(image, "new", pt1+Point(40,47), FONT_HERSHEY_PLAIN, 3.0, black, 2);
	putText(image, "load", pt2 + Point(40, 47), FONT_HERSHEY_PLAIN, 3.0, black, 2);
	cv::imshow("사각형", image);
	setMouseCallback("사각형", onMouse, 0);
	
	cv::waitKey(0);
	return 0;
}

void onMouse(int event, int x, int y, int flags, void *param) {
	Point click(x, y);
	switch (event) {
	case EVENT_LBUTTONDOWN:
		if (page == 1)
		{
			if (click.inside(rect1))
			{
				cout << "새로만들기" << endl;
				make_interface();
				page = 2;
			}
			else if (click.inside(rect2))
			{
				cout << "불러오기" << endl;
				page = 2;
			}
		}
		else if (page == 2)
		{
			for (int i = 0; i < 6; i++)
			{
				if (click.inside(btnarray[i]))
				{
					cout << i << endl;
					gui = i;
					change_gui(i);
				}
			}
		}
		if (click.inside(btnleftrect))
		{

		}
		else if (click.inside(btnrightrect))
		{
			makecode();
		}
		break;
	case EVENT_RBUTTONDOWN:
		cout << "마우스 우측버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONUP:
		cout << "마우스 왼쪽버튼 떼기" << endl;
		break;
	}
}
bool select[6] = { true ,true,true,true,true,true };
bool select2[12] = { true,true,true,true, true, true, true, true, true, true, true, true };
bool st = true;
int portcnt[6] = { 0,0,0,0,0,0 };
int flag = 0;
int stpre = 72;
int starr = 10;
bool extiselect[10] = { true , true, true, true, true, true, true, true, true, true };
bool extiselect2[10] = { true , true, true, true, true, true, true, true, true, true };
bool extiselect3[10] = { true , true, true, true, true, true, true, true, true, true };
bool extiselect4[10] = { true , true, true, true, true, true, true, true, true, true };
void guiMouse(int event, int x, int y, int flags, void *param)
{
	Point click(x, y);
	Rect check;
	char extiport;
	switch (event) {
	case EVENT_LBUTTONDOWN:
		switch (gui)
		{
		case 0:
			for (int i = 0; i < 6; i++)
			{
				if (click.inside(portarray[i]))
				{
					check = Rect(port_point_array[i] + Point(1, 1), inside);
					if (select[i])
					{
						rectangle(guiimage, check, black, FILLED);
						select[i] = false;
						port = i;
						for (int j = 0; j < 6; j++)
						{
							if (i != j)
							{
								check = Rect(port_point_array[j] + Point(1, 1), inside);
								rectangle(guiimage, check, white, FILLED);
								select[i] = true;
							}
						}
						cout << port<< endl;
						for (int j = 0; j < 12; j++)
						{
							check = Rect(gpiopointarray[j] + Point(1, 1), inside);
							if (portpin[i][j])
							{
								rectangle(guiimage, check, black, FILLED);
							}
							else
							{
								rectangle(guiimage, check, white, FILLED);
							}
						}
					}
					
					imshow("gui", guiimage);
					
				}
			}

			for (int i = 0; i < 12; i++)
			{
				if (click.inside(gpioarray[i]))
				{
					check = Rect(gpiopointarray[i] + Point(1, 1), inside);
					cout << "gpio" << i << endl;
					if (!(portpin[port][i]))
					{
						rectangle(guiimage, check, black, FILLED);
						portcnt[port]++;
						porten[port] = true;
						portpin[port][i] = true;
					}
					else
					{
						rectangle(guiimage, check, white, FILLED);
						portcnt[port]--;
						if (portcnt[port] == 0)
							porten[port] = false;
						portpin[port][i] = false;
						cout << i << endl;
					}
					imshow("gui", guiimage);
				}
			}
			break;
		case 1:
			for (int i = 0; i < 10; i++)
			{
				if (click.inside(extienrectarr[i]))
				{
					check = Rect(extienpointarr[i] + Point(1, 1), inside);
					if (!extien[i])
					{
						rectangle(guiimage, check, black, FILLED);
						extien[i] = true;
					}
					else
					{
						rectangle(guiimage, check, white, FILLED);
						extien[i] = false;
					}
				}
				else if (click.inside(extipinrectarr[i]))
				{
					check = Rect(extipinarr[i] + Point(1, 1), inside);
					if (extiselect2[i])
					{
						bool loop =true;
						rectangle(guiimage, check, black, FILLED);
						extiselect2[i] = false;
						while (loop)
						{
							cout << "사용할 핀을 입력해주세요." << endl;
							cin >> extiport;
							if (extiport >= 'A' && extiport <= 'F')
							{
								extipin[i] = extiport;
								loop = false;
							}
							else
							{
								cout << "대문자 A~F만 입력해주세요" << endl;
							}
						}
					}
					else
					{
						rectangle(guiimage, check, white, FILLED);
						extiselect2[i] = true;
						extien[i] = false;
					}
				}
				else if (click.inside(extirtarr[i]))
				{
					check = Rect(extirtpointarr[i] + Point(1, 1), inside);
					if (!extirt[i])
					{
						rectangle(guiimage, check, black, FILLED);
						extirt[i] = true;
					}
					else
					{
						rectangle(guiimage, check, white, FILLED);
						extirt[i] = false;
					}
				}
				else if (click.inside(extiftarr[i]))
				{
					check = Rect(extiftpointarr[i] + Point(1, 1), inside);
					if (!extift[i])
					{
						rectangle(guiimage, check, black, FILLED);
						extift[i] = true;
					}
					else
					{
						rectangle(guiimage, check, white, FILLED);
						extift[i] = false;
					}
				}
			}
			imshow("gui", guiimage);
			break;
		case 3:
			if (click.inside(stenrect))
			{
				if (st)
				{
					check = Rect(stenbtn + Point(1, 1), inside);
					rectangle(guiimage, check, black, FILLED);
					systicken = true;
					st = false;
				}
				else
				{
					check = Rect(stenbtn + Point(1, 1), inside);
					rectangle(guiimage, check, white, FILLED);
					systicken = false;
					st = true;
				}
				imshow("gui", guiimage);
			}
			else if (click.inside(inputrect))
			{

				if (flag != 2)
				{
					check = Rect(stinput + Point(1, 1), inside);
					rectangle(guiimage, check, black, FILLED);
					imshow("gui", guiimage);
					flag = 1;
					cout << "입력값" << endl;
					cin >> stpre;
					cout << "systick 클럭:" << (72000000 / stpre) << endl;
					flag = 0;
					rectangle(guiimage, check, white, FILLED);
					imshow("gui", guiimage);
				}
			}
		}

		break;
	case EVENT_RBUTTONDOWN:
		cout << "마우스 우측버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONUP:
		cout << "마우스 왼쪽버튼 떼기" << endl;
		break;
	}
}
void make_interface()
{
	
	rectangle(image, Point(0,0),Point(499,499), white,FILLED);

	for (int i = 0; i < 6; i++)
	{
		rectangle(image, btnarray[i], black, 2);
	}
	for (int i = 0; i < 6; i++)
	{
		putText(image, button_strings[i], btnpointarray[i]+Point(40, 47), FONT_HERSHEY_PLAIN, 1.0, black, 2);
	}
	if (page != 2)
	{


		rectangle(image, btnrightrect, black, 2);
		putText(image, "make", btnRight + Point(40, 37), FONT_HERSHEY_PLAIN, 1.0, black, 2);
	}
	else if (page != 3)
	{
		rectangle(image, btnleftrect, black, 2);
		putText(image, "before", btnleft + Point(40, 37), FONT_HERSHEY_PLAIN, 1.0, black, 2);
	}
	imshow("사각형", image);
}
void change_gui(int page)
{
	rectangle(guiimage, Point(0, 0), Point(499, 499), white, FILLED);
	switch (page)
	{
	case 0:
		for (int i = 0; i < 5; i++)
		{
			putText(guiimage, port_strings[i], port_point_array[i] - Point(5,35), FONT_HERSHEY_PLAIN, 1.0, black, 2);
			rectangle(guiimage, portarray[i], black, 2);
		}
		for (int i = 0; i < 12; i++)
		{
			rectangle(guiimage, gpioarray[i], black, 2);
		}
		break;
	case 1:
		for (int i = 0; i < 10; i++)
		{
			rectangle(guiimage, extienrectarr[i], black, 2);
		}
		for (int i = 0; i < 10; i++)
		{
			rectangle(guiimage, extipinrectarr[i], black, 2);
		}
		for (int i = 0; i < 10; i++)
		{
			rectangle(guiimage, extirtarr[i], black, 2);
		}
		for (int i = 0; i < 10; i++)
		{
			rectangle(guiimage, extiftarr[i], black, 2);
		}
		break;
	case 3:
		rectangle(guiimage, stenrect, black, 2);
		rectangle(guiimage, inputrect, black, 2);
		putText(guiimage, "enable", stentext, FONT_HERSHEY_PLAIN, 1.0, black, 1);
		putText(guiimage, "prescale", sttext, FONT_HERSHEY_PLAIN, 1.0, black, 1);
		break;

	}
	imshow("gui", guiimage);
	setMouseCallback("gui", guiMouse, 0);
}
void makecode()
{
	int apb2enr = 0;
	int CRL = 0;
	int CRH = 0;
	int data = 0;
	int rtsr = 0;
	int ftsr = 0;
	int AFIO1 = 0;
	int AFIO2 = 0;
	int AFIO3 = 0;
	int ISER = 0;
	int ISER2 = 0;
	int IMR = 0;
	bool gpioen = false;
	bool is_exti = false;
	char portset;
	ofstream outFile("output.txt");
	outFile << "//GPIO CLEAR" << endl;
	for (int i = 0; i < 5; i++)
	{
		portset = charportstring[i];
		if (porten[i])
		{
			gpioen = true;
			apb2enr += 1 << (2 + i);
			outFile << "GPIO" << portset << "->CRL = " << 0 << ";" << endl;
			outFile << "GPIO" << portset << "->CRH = " << 0 << ";" << endl;
		}
	}
	outFile << "//NVIC CLEAR" << endl;
	outFile << "NVIC->ISER[0] = 0;" << endl;
	outFile << "NVIC->ISER[1] = 0;" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (extien[i])
		{
			is_exti = true;
			if (i < 5)
			{
				ISER += (1 << (i + 6));
			}
			else if (i < 10)
			{
				ISER |= (1 << 23);
			}
			else if (i == 10)
			{
				ISER2 = (1 << 12);
			}
			IMR += (1 << i);
		}
	}
	if (is_exti)
		apb2enr += 1;
	outFile << endl << "//CLOCK EN" << endl;
	outFile << "RCC->APB2ENR |= " << apb2enr << ";" << endl;

	outFile << endl << "//GPIO SETTING" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (porten[i])
		{
			portset = charportstring[i];
			for (int j = 0; j < 8; j++)
			{
				if (portpin[i][j])
				{
					CRL += 0x3 << (j * 4);
				}
				else
				{
					CRL += 0x4 << (j * 4);
				}
			}
			for (int j = 8; j < 12; j++)
			{
				if (portpin[i][j])
				{
					CRH += 0x3 << ((j - 8) * 4);
				}
				else
				{
					CRH += 0x4 << ((j - 8) * 4);
				}
			}
			outFile << "GPIO" << portset << "->CRL = " << CRL << ";" << endl;
			outFile << "GPIO" << portset << "->CRH = " << CRH << ";"<< endl;
		}
		outFile << endl;
	}
	for (int i = 0; i < 10; i++)
	{
		if (extirt[i])
		{
			rtsr += (1 << i);
		}
		if (extift[i])
		{
			ftsr += (1 << i);
		}
		if (i >= 8)
		{
			AFIO3 += (extipin[i] - 'A')<<(i-8);
		}
		else if (i >= 4)
		{
			AFIO2 += (extipin[i] - 'A') << (i - 4);
		}
		else
		{
			AFIO1 += (extipin[i] - 'A') << i;
		}
	}
	if (systicken)
	{
		outFile << "SysTick->LOAD = " << stpre << ";//systick scale "<< stpre << endl;
		outFile << "SysTick->CTRL=0x07;//systick enable"<< endl;
	}
	outFile << endl << "//INTERRUPT ENABLE" << endl;
	outFile << "NVIC->ISER[0] |= " << ISER << ";" << endl;
	outFile << "NVIC->ISER[1] |= " << ISER2 << ";" << endl;
	outFile << "EXTI->IMR |= " << IMR << ";" << endl;
	outFile << "EXTI->FTSR |= " << ftsr << ";" << endl;
	outFile << "EXTI->RTSR |= " << rtsr << ";" << endl;
	cout << "코드생성 완료" << endl;
}