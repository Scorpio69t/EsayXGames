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

		// �ɽǶȾ��������յ�����
		secondEnd.x = center.x + secondLenth * sin(secondAngle);
		secondEnd.y = center.y - secondLenth * cos(secondAngle);

		// �ɽǶȾ��������յ�����
		minuteEnd.x = center.x + minuteLenth * sin(minuteAngle);
		minuteEnd.y = center.y - minuteLenth * cos(minuteAngle);

		// �ɽǶȾ���ʱ���յ�����
		hourEnd.x = center.x + hourLenth * sin(hourAngle);
		hourEnd.y = center.y - hourLenth * cos(hourAngle);

		// ������
		setlinestyle(PS_SOLID, 2); // ��ʵ�ߣ����Ϊ2������
		setcolor(WHITE);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		// ������
		setlinestyle(PS_SOLID, 4); // ��ʵ�ߣ����Ϊ4������
		setcolor(BLUE);
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);

		// ��ʱ��
		setlinestyle(PS_SOLID, 6); // ��ʵ�ߣ����Ϊ6������
		setcolor(RED);
		line(center.x, center.y, hourEnd.x, hourEnd.y);

		Sleep(10); // ��ʱ10����

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2); // ��ʵ�ߣ����Ϊ2������
		line(center.x, center.y, secondEnd.x, secondEnd.y);
		setlinestyle(PS_SOLID, 4); // ��ʵ�ߣ����Ϊ4������
		line(center.x, center.y, minuteEnd.x, minuteEnd.y);
		setlinestyle(PS_SOLID, 6); // ��ʵ�ߣ����Ϊ6������
		line(center.x, center.y, hourEnd.x, hourEnd.y);
	}

	int c = _getch();
	closegraph();

	return 0;
}
