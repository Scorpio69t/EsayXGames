#include <graphics.h>
#include <conio.h>
#include <cmath>

using namespace std;

struct Point
{
	int x;
	int y;
};

#define High 480
#define Width 640
#define PI 3.1415926

int main(void)
{
	initgraph(Width, High);
	Point center, secondEnd, minuteEnd, hourEnd;
	center.x = Width / 2;
	center.y = High / 2;
	int secondLenth = Width / 5;
	int minuteLenth = Width / 6;
	int hourLenth = Width / 8;

	double secondAngle;
	double minuteAngle;
	double hourAngle;

	SYSTEMTIME ti;

	while (true)
	{
		GetLocalTime(&ti);

		secondAngle = ti.wSecond * 2 * PI / 60;
		minuteAngle = ti.wMinute * 2 * PI / 60;
		hourAngle = (ti.wHour % 12) * 2 * PI / 12;

		// 由角度决定秒针终点坐标
		secondEnd.x = center.x + secondLenth * sin(secondAngle);
		secondEnd.y = center.y - secondLenth * cos(secondAngle);

		// 由角度决定分针终点坐标
		minuteEnd.x = center.x + minuteLenth * sin(minuteAngle);
		minuteEnd.y = center.y - minuteLenth * cos(minuteAngle);

		// 由角度决定时针终点坐标
		hourEnd.x = center.x + hourLenth * sin(hourAngle);
		hourEnd.y = center.y - hourLenth * cos(hourAngle);

		// 画秒针
		setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
		setcolor(WHITE);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		// 画分针
		setlinestyle(PS_SOLID, 4); // 画实线，宽度为4个像素
		setcolor(BLUE);
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);

		// 画时针
		setlinestyle(PS_SOLID, 6); // 画实线，宽度为6个像素
		setcolor(RED);
		line(center.x, center.y, hourEnd.x, hourEnd.y);

		Sleep(10); // 延时10毫秒

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
		line(center.x, center.y, secondEnd.x, secondEnd.y);
		setlinestyle(PS_SOLID, 4); // 画实线，宽度为4个像素
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);
		setlinestyle(PS_SOLID, 6); // 画实线，宽度为6个像素
		line(center.x, center.y, hourEnd.x, hourEnd.y);
	}

	int c = _getch();
	closegraph();

	return 0;
}
