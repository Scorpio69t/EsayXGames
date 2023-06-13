@[TOC](目录)
# 反弹球消砖块
本博客介绍利用EasyX加上图片、音乐素材实现一个鼠标控制的飞机大战小游戏。
本文源码可从[github](https://github.com/Scorpio69t/EsayXGames)获取

## 1. 用鼠标控制飞机移动
第一步实现鼠标控制飞机移动。
```cpp
#include <graphics.h>
#include <conio.h>

#pragma comment(lib, "Winmm.lib")

#define High 864
#define Width 591

struct Point
{
	int x;
	int y;
};

IMAGE img_bk; // 背景图片
Point position; // 飞机位置
IMAGE img_planeNormal1, img_planeNormal2; // 飞机图片

void startup() 
{
	initgraph(Width, High);
	loadimage(&img_bk, _T("res\\background.jpg"));
	loadimage(&img_planeNormal1, _T("res\\planeNormal_1.jpg"));
	loadimage(&img_planeNormal2, _T("res\\planeNormal_2.jpg"));
	position.x = High * 0.7;
	position.y = Width * 0.5;
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	putimage(position.x-50, position.y-60, &img_planeNormal1, NOTSRCERASE);
	putimage(position.x-50, position.y-60, &img_planeNormal2, SRCINVERT);
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{

}

void updateWithInput()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			position.x = m.x;
			position.y = m.y;
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main(void)
{
	startup();
	while (true)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}

	gameover();

	return 0;
}
```
![1](https://img-blog.csdnimg.cn/7eca581d1fad4dee8dd993db2009336b.png)

## 2. 发射子弹
第二步按下鼠标左键后飞机发射子弹，子弹图片为bullet1.jpg和bullet2.jpg。
```cpp
#include <graphics.h>
#include <conio.h>

// 引用Windows Multimedia Library
#pragma comment(lib, "Winmm.lib")

#define High 864
#define Width 591

struct Point
{
	int x;
	int y;
};

IMAGE img_bk; // 背景图片
Point position; // 飞机位置
Point bullet; // 子弹位置
IMAGE img_planeNormal1, img_planeNormal2; // 飞机图片
IMAGE img_bullet1, img_bullet2; // 子弹图片

void startup() 
{
	initgraph(Width, High);
	loadimage(&img_bk, _T("res\\background.jpg"));
	loadimage(&img_planeNormal1, _T("res\\planeNormal_1.jpg"));
	loadimage(&img_planeNormal2, _T("res\\planeNormal_2.jpg"));
	loadimage(&img_bullet1, _T("res\\bullet1.jpg"));
	loadimage(&img_bullet2, _T("res\\bullet2.jpg"));
	position.x = High * 0.7;
	position.y = Width * 0.5;
	bullet.x = position.x;
	bullet.y = -85; // 子弹初始位置
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	putimage(position.x-50, position.y-60, &img_planeNormal1, NOTSRCERASE);
	putimage(position.x-50, position.y-60, &img_planeNormal2, SRCINVERT);
	putimage(bullet.x-7, bullet.y, &img_bullet1, NOTSRCERASE);
	putimage(bullet.x-7, bullet.y, &img_bullet2, SRCINVERT);
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (bullet.y > -25) {
		bullet.y -= 3;
	}
}

void updateWithInput()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			position.x = m.x;
			position.y = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			bullet.x = position.x;
			bullet.y = position.y - 85;
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main(void)
{
	startup();
	while (true)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}

	gameover();

	return 0;
}
```
![2](https://img-blog.csdnimg.cn/dd9c06b736514a3595e3965f3c8afd54.png)



## 3. 增加敌机
第三步增加敌机自动向下运动，从下边界消失后会重新出现，敌机图片为enemyPlane1.jpg和enemyPlane2.jpg。

```cpp
#include <graphics.h>
#include <conio.h>

// 引用Windows Multimedia Library
#pragma comment(lib, "Winmm.lib")

#define High 864
#define Width 591

struct Point
{
	int x;
	int y;
};

struct fPoint 
{
	float x;
	float y;
};

IMAGE img_bk; // 背景图片
Point position; // 飞机位置
Point bullet; // 子弹位置
fPoint enemy; // 敌机位置
IMAGE img_planeNormal1, img_planeNormal2; // 飞机图片
IMAGE img_bullet1, img_bullet2; // 子弹图片
IMAGE img_enemyPlane1, img_enemyPlane2; // 敌机图片

void startup() 
{
	initgraph(Width, High);
	loadimage(&img_bk, _T("res\\background.jpg"));
	loadimage(&img_planeNormal1, _T("res\\planeNormal_1.jpg"));
	loadimage(&img_planeNormal2, _T("res\\planeNormal_2.jpg"));
	loadimage(&img_bullet1, _T("res\\bullet1.jpg"));
	loadimage(&img_bullet2, _T("res\\bullet2.jpg"));
	loadimage(&img_enemyPlane1, _T("res\\enemyPlane1.jpg"));
	loadimage(&img_enemyPlane2, _T("res\\enemyPlane2.jpg"));
	position.x = High * 0.7;
	position.y = Width * 0.5;
	bullet.x = position.x;
	bullet.y = -85; // 子弹初始位置
	enemy.x = Width * 0.5;
	enemy.y = 10;
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	putimage(position.x-50, position.y-60, &img_planeNormal1, NOTSRCERASE);
	putimage(position.x-50, position.y-60, &img_planeNormal2, SRCINVERT);
	putimage(bullet.x-7, bullet.y, &img_bullet1, NOTSRCERASE);
	putimage(bullet.x-7, bullet.y, &img_bullet2, SRCINVERT);
	putimage(enemy.x, enemy.y, &img_enemyPlane1, NOTSRCERASE);
	putimage(enemy.x, enemy.y, &img_enemyPlane2, SRCINVERT);
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (bullet.y > -25) {
		bullet.y -= 3;
	}
	if (enemy.y < High - 25) {
		enemy.y += 0.5;
	}
	else {
		enemy.y = 10;
	}
}

void updateWithInput()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			position.x = m.x;
			position.y = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			bullet.x = position.x;
			bullet.y = position.y - 85;
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main(void)
{
	startup();
	while (true)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}

	gameover();

	return 0;
}
```
![3](https://img-blog.csdnimg.cn/2cd4b617497542bf8ed7a7fc9d1fff6f.png)



## 4. 判断胜败
第四步增加子弹击中敌机、敌机撞击我机的判断，并增加我机爆炸的图片效果。
```cpp
#include <graphics.h>
#include <conio.h>
#include <math.h>

// 引用Windows Multimedia Library
#pragma comment(lib, "Winmm.lib")

#define High 864
#define Width 591

struct Point
{
	int x;
	int y;
};

struct fPoint 
{
	float x;
	float y;
};

IMAGE img_bk; // 背景图片
Point position; // 飞机位置
Point bullet; // 子弹位置
fPoint enemy; // 敌机位置
IMAGE img_planeNormal1, img_planeNormal2; // 飞机图片
IMAGE img_planeExplode1, img_planeExplode2; // 飞机爆炸图片
IMAGE img_bullet1, img_bullet2; // 子弹图片
IMAGE img_enemyPlane1, img_enemyPlane2; // 敌机图片
bool isExpolde = false; // 飞机是否爆炸

void startup() 
{
	initgraph(Width, High);
	loadimage(&img_bk, _T("res\\background.jpg"));
	loadimage(&img_planeNormal1, _T("res\\planeNormal_1.jpg"));
	loadimage(&img_planeNormal2, _T("res\\planeNormal_2.jpg"));
	loadimage(&img_bullet1, _T("res\\bullet1.jpg"));
	loadimage(&img_bullet2, _T("res\\bullet2.jpg"));
	loadimage(&img_enemyPlane1, _T("res\\enemyPlane1.jpg"));
	loadimage(&img_enemyPlane2, _T("res\\enemyPlane2.jpg"));
	loadimage(&img_planeExplode1, _T("res\\planeExplode_1.jpg"));
	loadimage(&img_planeExplode2, _T("res\\planeExplode_2.jpg"));
	position.x = High * 0.7;
	position.y = Width * 0.5;
	bullet.x = position.x;
	bullet.y = -85; // 子弹初始位置
	enemy.x = Width * 0.5;
	enemy.y = 10;
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	if (!isExpolde) {
		putimage(position.x - 50, position.y - 60, &img_planeNormal1, NOTSRCERASE);
		putimage(position.x - 50, position.y - 60, &img_planeNormal2, SRCINVERT);
		putimage(bullet.x - 7, bullet.y, &img_bullet1, NOTSRCERASE);
		putimage(bullet.x - 7, bullet.y, &img_bullet2, SRCINVERT);
		putimage(enemy.x, enemy.y, &img_enemyPlane1, NOTSRCERASE);
		putimage(enemy.x, enemy.y, &img_enemyPlane2, SRCINVERT);
	}
	else {
		putimage(position.x - 50, position.y - 60, &img_planeExplode1, NOTSRCERASE);
		putimage(position.x - 50, position.y - 60, &img_planeExplode2, SRCINVERT);
	}
	
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (bullet.y > -25) {
		bullet.y -= 3;
	}

	if (enemy.y < High - 25) {
		enemy.y += 0.5;
	}
	else {
		enemy.y = 10;
	}

	if (fabs(bullet.x - enemy.x) + fabs(bullet.y - enemy.y) < 50) { // 子弹击中敌机
		enemy.x = rand() % Width;
		enemy.y = -40;
		bullet.y = -85;
	}

	if (fabs(position.x - enemy.x) + fabs(position.y - enemy.y) < 150) { // 敌机撞击我机
		isExpolde = true;
	}
}

void updateWithInput()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			position.x = m.x;
			position.y = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			bullet.x = position.x;
			bullet.y = position.y - 85;
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main(void)
{
	startup();
	while (true)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}

	gameover();

	return 0;
}
```
![4](https://img-blog.csdnimg.cn/396b55049fa449a8bff0a5f71c854f74.png)
## 5. 增加音效
第五步增加背景音乐、发射子弹音效、飞机爆炸音效、得分鼓励音效。
```cpp
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

// 引用Windows Multimedia Library
#pragma comment(lib, "Winmm.lib")

#define High 864
#define Width 591

struct Point
{
	int x;
	int y;
};

struct fPoint 
{
	float x;
	float y;
};

IMAGE img_bk; // 背景图片
Point position; // 飞机位置
Point bullet; // 子弹位置
fPoint enemy; // 敌机位置
IMAGE img_planeNormal1, img_planeNormal2; // 飞机图片
IMAGE img_planeExplode1, img_planeExplode2; // 飞机爆炸图片
IMAGE img_bullet1, img_bullet2; // 子弹图片
IMAGE img_enemyPlane1, img_enemyPlane2; // 敌机图片
bool isExpolde = false; // 飞机是否爆炸
int score = 0; // 得分

void startup() 
{
	mciSendString(LPCWSTR("open res\\game_music.mp3 alias bkmusic"), NULL, 0, NULL); // 打开背景音乐
	mciSendString(LPCWSTR("play bkmusic repeat"), NULL, 0, NULL); // 循环播放背景音乐
	initgraph(Width, High);
	loadimage(&img_bk, _T("res\\background.jpg"));
	loadimage(&img_planeNormal1, _T("res\\planeNormal_1.jpg"));
	loadimage(&img_planeNormal2, _T("res\\planeNormal_2.jpg"));
	loadimage(&img_bullet1, _T("res\\bullet1.jpg"));
	loadimage(&img_bullet2, _T("res\\bullet2.jpg"));
	loadimage(&img_enemyPlane1, _T("res\\enemyPlane1.jpg"));
	loadimage(&img_enemyPlane2, _T("res\\enemyPlane2.jpg"));
	loadimage(&img_planeExplode1, _T("res\\planeExplode_1.jpg"));
	loadimage(&img_planeExplode2, _T("res\\planeExplode_2.jpg"));
	position.x = High * 0.7;
	position.y = Width * 0.5;
	bullet.x = position.x;
	bullet.y = -85; // 子弹初始位置
	enemy.x = Width * 0.5;
	enemy.y = 10;
	BeginBatchDraw();
}

void show()
{
	putimage(0, 0, &img_bk);
	if (!isExpolde) {
		putimage(position.x - 50, position.y - 60, &img_planeNormal1, NOTSRCERASE);
		putimage(position.x - 50, position.y - 60, &img_planeNormal2, SRCINVERT);
		putimage(bullet.x - 7, bullet.y, &img_bullet1, NOTSRCERASE);
		putimage(bullet.x - 7, bullet.y, &img_bullet2, SRCINVERT);
		putimage(enemy.x, enemy.y, &img_enemyPlane1, NOTSRCERASE);
		putimage(enemy.x, enemy.y, &img_enemyPlane2, SRCINVERT);
	}
	else {
		putimage(position.x - 50, position.y - 60, &img_planeExplode1, NOTSRCERASE);
		putimage(position.x - 50, position.y - 60, &img_planeExplode2, SRCINVERT);
	}

	outtextxy(Width * 0.48, High * 0.95, _T("得分: "));
	char s[5] = { 0 };
	sprintf(s, "%d", score);
	outtextxy(Width * 0.55, High * 0.95, TCHAR(s));
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	if (bullet.y > -25) {
		bullet.y -= 3;
	}

	if (enemy.y < High - 25) {
		enemy.y += 0.5;
	}
	else {
		enemy.y = 10;
	}

	if (fabs(bullet.x - enemy.x) + fabs(bullet.y - enemy.y) < 80) { // 子弹击中敌机
		enemy.x = rand() % Width;
		enemy.y = -40;
		bullet.y = -85;
		mciSendString(LPCWSTR("close gemusic"), NULL, 0, NULL); // 关闭上一次的音乐
		mciSendString(LPCWSTR("open gotEnemy.mp3 alias gemusic"), NULL, 0, NULL);

		mciSendString(LPCWSTR("play gemusic"), NULL, 0, NULL); // 播放音乐
		score++;
		if (score > 0 && score % 5 == 0 && score % 2 != 0)
		{
			mciSendString(LPCWSTR("close 5music"), NULL, 0, NULL); // 关闭上一次的音乐
			mciSendString(LPCWSTR("open 5.mp3 alias 5music"), NULL, 0, NULL);

			mciSendString(LPCWSTR("play 5music"), NULL, 0, NULL); // 播放音乐
		}

		if (score % 10 == 0)
		{
			mciSendString(LPCWSTR("close 10music"), NULL, 0, NULL); // 关闭上一次的音乐
			mciSendString(LPCWSTR("open 10.mp3 alias 10music"), NULL, 0, NULL);

			mciSendString(LPCWSTR("play 10music"), NULL, 0, NULL); // 播放音乐
		}
	}

	if (fabs(position.x - enemy.x) + fabs(position.y - enemy.y) < 150) { // 敌机撞击我机
		isExpolde = true;
		mciSendString(LPCWSTR("close exmusic"), NULL, 0, NULL); // 关闭上一次的音乐
		mciSendString(LPCWSTR("open explode.mp3 alias exmusic"), NULL, 0, NULL);

		mciSendString(LPCWSTR("play exmusic"), NULL, 0, NULL); // 播放音乐
	}
}

void updateWithInput()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			position.x = m.x;
			position.y = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			bullet.x = position.x;
			bullet.y = position.y - 85;
			mciSendString(LPCWSTR("close fgmusic"), NULL, 0, NULL); // 关闭上一次的音乐
			mciSendString(LPCWSTR("open f_gun.mp3 alias fgmusic"), NULL, 0, NULL);

			mciSendString(LPCWSTR("play fgmusic"), NULL, 0, NULL); // 播放音乐
		}
	}
}

void gameover()
{
	EndBatchDraw();
	_getch();
	closegraph();
}

int main(void)
{
	startup();
	while (true)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}

	gameover();

	return 0;
}
```
![5](https://img-blog.csdnimg.cn/6c845ba1aa7741e5b6b7c142b2762dd5.png)

至此完成。