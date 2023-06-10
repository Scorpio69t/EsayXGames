# 实时时钟
本博客介绍利用EasyX实现一个实时钟表的小程序，同时学习时间函数的使用。
## 1. 绘制静态秒针
第一步定义钟表的中心坐标center，它也是秒针的起点；定义秒针的长度secondLength、秒针的终点坐标secondEnd；利用setlinestyle函数设定线的型号和宽度，调用line函数绘制秒针。
```cpp
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

int main(void)
{
	initgraph(Width, High);
	Point center, secondEnd;
	center.x = Width / 2;
	center.y = High / 2;
	int sencondLenth = Width / 5;

	secondEnd.x = center.x + sencondLenth;
	secondEnd.y = center.y;

	// 画秒针
	setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
	setcolor(WHITE);
	line(center.x, center.y, secondEnd.x, secondEnd.y);
	_getch();
	closegraph();

	return 0;
}
```
![1](https://img-blog.csdnimg.cn/dbd92ad122fe40938d8b6f4764df8d0c.png)
## 2. 秒针的转动
第二步实现秒针的转动，定义secondAngle为秒针对应的角度，利用三角几何知识求出秒针的终点坐标：
		**secondEnd.x = center.x + secondLenth * sin(secondAngle);**
		**secondEnd.y = center.y - secondLenth * cos(secondAngle);**
让角度循环变化，则实现了秒针转动的动画效果。
```cpp
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
	Point center, secondEnd;
	center.x = Width / 2;
	center.y = High / 2;
	int secondLenth = Width / 5;

	secondEnd.x = center.x + secondLenth;
	secondEnd.y = center.y;

	double secondAngle = 1.0; 

	while (true)
	{
		// 由角度决定终点坐标
		secondEnd.x = center.x + secondLenth * sin(secondAngle);
		secondEnd.y = center.y - secondLenth * cos(secondAngle);

		// 画秒针
		setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
		setcolor(WHITE);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		Sleep(100);

		setcolor(BLACK);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		// 秒针角度变化
		secondAngle = secondAngle * 2 * PI / 60 + 1;
	}

	_getch();
	closegraph();

	return 0;
}
```
![2](https://img-blog.csdnimg.cn/caa0424142da49f183fa2eb872e3e6f8.png)
# 3. 根据实际时间转动
第三步定义系统变量(SYSTEMTIME ti)，通过GetLocalTime(&ti)获取当前时间，秒针的角度由实际时间决定，即secondAngle = ti.wSecond * 2 * PI/60。
```cpp
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
	Point center, secondEnd;
	center.x = Width / 2;
	center.y = High / 2;
	int secondLenth = Width / 5;

	secondEnd.x = center.x + secondLenth;
	secondEnd.y = center.y;

	double secondAngle;
	SYSTEMTIME ti;

	while (true)
	{
		GetLocalTime(&ti);
		secondAngle = ti.wSecond * 2 * PI / 60;

		// 由角度决定终点坐标
		secondEnd.x = center.x + secondLenth * sin(secondAngle);
		secondEnd.y = center.y - secondLenth * cos(secondAngle);

		// 画秒针
		setlinestyle(PS_SOLID, 2); // 画实线，宽度为2个像素
		setcolor(WHITE);
		line(center.x, center.y, secondEnd.x, secondEnd.y);

		Sleep(100);

		setcolor(BLACK);
		line(center.x, center.y, secondEnd.x, secondEnd.y);
	}

	_getch();
	closegraph();

	return 0;
}
```
![3](https://img-blog.csdnimg.cn/ba33e4be8b5a4e48bd9d6d279f4b3b42.png)

## 4. 添加时针和分针
第四步添加时针、分针，和秒针变化相比，他们的长度、宽度、颜色、旋转速度有一定的不同。
```cpp
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
```
![4](https://img-blog.csdnimg.cn/2ed3f1fd66c249d0b9838b4b280fa59d.png)
## 5. 添加表盘刻度
第五步绘制表盘，并可以利用outtextxy()函数在画面中输出文字，为了让时针、分针的转动更自然，对求解时针、分针的角度进行了改进。
```cpp
```