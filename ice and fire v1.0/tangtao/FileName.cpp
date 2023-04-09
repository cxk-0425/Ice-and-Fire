#include<stdio.h>
#include<windows.h>
#include<graphics.h>   //画布上的一系列操作
#include<time.h>	//有各种时间函数
#include<conio.h>	//按键操作
#include<mmSystem.h>   //播放音乐
#pragma comment (lib,"winmm.lib")	//导入winmm.lib库

//毒液是水平720到800，高度540到568
//冰面是水平560到610，下高度685以上
//火面是790到850
// 转换器（水平301到337，竖直508到523）
#define poisonleft 720
#define poisonright 800
#define poisonheight 540
#define poisondown	568
#define iceleft	560
#define iceright 610	
#define iceheight 685
#define fireleft 790
#define fireright 850
#define fireheight 685
#define switchleft 301
#define switchright 337
#define switchheight 508
#define switchdown 523

#define time 1.0/60		//时间
#define widthleft 43	//左宽度	x+widthleft是小人左边
#define widthright 55	//右宽度	x+widthright是小人右边界
#define lengthup 30		//上高度
#define lengthdown 77	//下高度

#define edgeleft 50		//左边缘
#define edgeright 1050	//右边缘
#define DOORWIDTH 60	//门宽
#define DOORHEIGHT 123	//门高
#define ICEDOORX 875	
#define ICEDOORY 75		//冰门位置左下角位置
#define FIREDOORX 950
#define FIREDOORY 75	//火门位置左下角位置

#define vx 260		//水平速度
#define vy 500		//竖直速度
#define ax 250		//水平加速度
#define ay 1200		//竖直加速度

PIMAGE ICEDOOR0, ICEDOOR1, ICEDOOR2, ICEDOOR3, ICEDOOR4,
FIREDOOR0, FIREDOOR1, FIREDOOR2, FIREDOOR3, FIREDOOR4,
_enter, _back1, _back2, _barrier1, _dead, succeeded, _start,
_explanationbt, _about, _explanation, _firestill, _fireup, _firedown,
_fireleft, _fireright, _firelu, _fireld, _fireru, _firerd, _icestill, _iceup,
_icedown, _iceleft, _iceright, _icelu, _iceld, _iceru, _icerd, SWITCH, lift;

char A, B, C, D;
int firedoormode = 24, icedoormode = 24;
int barrier = 0, lifty = 350;
double initial_firex[100] = { 100 },
initial_firey[100] = { 500 },
firex = 0, firey = 0,
initial_icex[100] = { 100 },
initial_icey[600] = { 600 }, icex = 0, icey = 0;
double firevx = 0, firevy = 0, icevx = 0, icevy = 0;
mouse_msg msg = { 0 };

//地面坐标，构建一个可以容纳3关，每关可以有100个坐标的数组
typedef struct model1		//地面
{
	int x1 = 0, x2 = 1100, y1 = 699, y2 = 714;//714
}model1_;
model1_ floor[3][100], roof[3][100];
typedef struct model2		//墙壁
{
	int x = 369, y1 = 617, y2 = 621;
}model2_;
model2_ wallleft[3][100], wallright[3][100];

void datainitial()	//数据初始化
{
	firedoormode = 24, icedoormode = 24;
	lifty = 350;
	firex = initial_firex[0];
	firey = initial_firey[0];
	icex = initial_icex[0];
	icey = initial_icey[0];
	firevx = 0, firevy = 0, icevx = 0, icevy = 0;
	floor[0][15].y1 = 368, floor[0][15].y2 = 383;
}
void initial()
{
	//初始化图片
	succeeded = newimage();
	_explanation = newimage();
	_dead = newimage();
	SWITCH = newimage();
	lift = newimage();
	_enter = newimage();
	_back1 = newimage();
	_back2 = newimage();
	_barrier1 = newimage();
	_start = newimage();
	_about = newimage();
	_explanationbt = newimage();
	_icestill = newimage();
	_iceup = newimage();
	_icedown = newimage();
	_iceleft = newimage();
	_iceright = newimage();
	_icelu = newimage();
	_iceld = newimage();
	_iceru = newimage();
	_icerd = newimage();
	_firestill = newimage();
	_fireup = newimage();
	_firedown = newimage();
	_fireleft = newimage();
	_fireright = newimage();
	_firelu = newimage();
	_fireld = newimage();
	_fireru = newimage();
	_firerd = newimage();
	FIREDOOR0 = newimage();
	FIREDOOR1 = newimage();
	FIREDOOR2 = newimage();
	FIREDOOR3 = newimage();
	FIREDOOR4 = newimage();
	ICEDOOR0 = newimage();
	ICEDOOR1 = newimage();
	ICEDOOR2 = newimage();
	ICEDOOR3 = newimage();
	ICEDOOR4 = newimage();

	getimage(succeeded, "pictures//成功.jpg");
	getimage(_dead, "pictures//死亡.jpg");
	getimage(_explanation, "pictures//游戏说明.jpg");
	getimage(lift, "pictures//升降台.png");
	getimage(SWITCH, "pictures//地面机关.png");
	getimage(_enter, "pictures//进入界面.jpg");
	getimage(_back1, "pictures//地图.jpg");
	getimage(_barrier1, "pictures//游戏关卡1.png");
	getimage(_back2, "pictures//关于我们的游戏.jpg");
	getimage(_start, "pictures//开始按钮.png");
	getimage(_explanationbt, "pictures//游戏说明.png");
	getimage(_about, "pictures//关于我们.png");
	getimage(_icestill, "pictures//冰娃静.png");
	getimage(_iceup, "pictures//冰娃上.png");
	getimage(_icedown, "pictures//冰娃下.png");
	getimage(_iceright, "pictures//冰娃右.png");
	getimage(_iceleft, "pictures//冰娃左.png");
	getimage(_icelu, "pictures//冰娃左上.png");
	getimage(_iceru, "pictures//冰娃右上.png");
	getimage(_iceld, "pictures//冰娃左下.png");
	getimage(_icerd, "pictures//冰娃右下.png");
	getimage(_firestill, "pictures//火娃静.png");
	getimage(_fireup, "pictures//火娃上.png");
	getimage(_firedown, "pictures//火娃下.png");
	getimage(_fireright, "pictures//火娃右.png");
	getimage(_fireleft, "pictures//火娃左.png");
	getimage(_firelu, "pictures//火娃左上.png");
	getimage(_fireru, "pictures//火娃右上.png");
	getimage(_fireld, "pictures//火娃左下.png");
	getimage(_firerd, "pictures//火娃右下.png");
	getimage(FIREDOOR0, "pictures//火门0.png");
	getimage(FIREDOOR1, "pictures//火门1.png");
	getimage(FIREDOOR2, "pictures//火门2.png");
	getimage(FIREDOOR3, "pictures//火门3.png");
	getimage(FIREDOOR4, "pictures//火门4.png");
	getimage(ICEDOOR0, "pictures//冰门0.png");
	getimage(ICEDOOR1, "pictures//冰门1.png");
	getimage(ICEDOOR2, "pictures//冰门2.png");
	getimage(ICEDOOR3, "pictures//冰门3.png");
	getimage(ICEDOOR4, "pictures//冰门4.png");

	//地板横坐标
	floor[0][1].x1 = 36, floor[0][1].x2 = 369;		floor[0][1].y1 = 605, floor[0][1].y2 = 620;		//火人初始地板
	floor[0][2].x1 = 974, floor[0][2].x2 = 1060;	floor[0][2].y1 = 655, floor[0][2].y2 = 670;		//右下角梯形下平台
	floor[0][3].x1 = 1019, floor[0][3].x2 = 1060;	floor[0][3].y1 = 609, floor[0][3].y2 = 624;		//右下角上平台
	floor[0][4].x1 = 36, floor[0][4].x2 = 505;		floor[0][4].y1 = 508, floor[0][4].y2 = 523;		//毒液那行左半边的地面
	floor[0][5].x1 = 446, floor[0][5].x2 = 919;		floor[0][5].y1 = 553, floor[0][5].y2 = 568;		//毒液的行地面
	floor[0][6].x1 = 148, floor[0][6].x2 = 575;		floor[0][6].y1 = 380, floor[0][6].y2 = 395;		//转换器行左端的地面
	floor[0][7].x1 = 508, floor[0][7].x2 = 1060;	floor[0][7].y1 = 408, floor[0][7].y2 = 423;		//转换器行右端的地面
	floor[0][8].x1 = 36, floor[0][8].x2 = 190;		floor[0][8].y1 = 196, floor[0][8].y2 = 211;		//从上到下第2行左梯形上地面???
	floor[0][16].x1 = 179, floor[0][16].x2 = 240;	floor[0][16].y1 = 240, floor[0][16].y2 = 250;		//从上到下第2行左梯形右边地面
	floor[0][9].x1 = 200, floor[0][9].x2 = 949;		floor[0][9].y1 = 284, floor[0][9].y2 = 299;		//从第2行左边梯形右端一直到最右边地面
	floor[0][10].x1 = 532, floor[0][10].x2 = 730;	floor[0][10].y1 = 250, floor[0][10].y2 = 265;	//第2行中间突出的一块平地
	//floor[0][11].x1 = 277, floor[0][11].x2 = 430;	floor[0][11].y1 = 151, floor[0][11].y2 = 166;	//门那一行左边梯形下边界
	floor[0][12].x1 = 318, floor[0][12].x2 = 393;	floor[0][12].y1 = 108, floor[0][12].y2 = 123;	//门那一行左边梯形上边界
	floor[0][13].x1 = 277, floor[0][13].x2 = 1060;	floor[0][13].y1 = 151, floor[0][13].y2 = 166;	//门的大横行
	//floor[0][14].x1 = 0, floor[0][14].x2 = 190;		floor[0][14].y1 = 196, floor[0][14].y2 = 211;	//第二行左边梯形
	floor[0][15].x1 = 10, floor[0][15].x2 = 150;	floor[0][15].y1 = 368, floor[0][15].y2 = 383;	//转换器木板



	//顶板
	roof[0][1].x1 = 64, roof[0][1].x2 = 369;	roof[0][1].y1 = 618, roof[0][1].y2 = 633;	//冰火娃起始位置的冰头顶
	roof[0][2].x1 = 64, roof[0][2].x2 = 505;	roof[0][2].y1 = 516, roof[0][2].y2 = 534;	//起始位置火娃头顶
	roof[0][3].x1 = 446, roof[0][3].x2 = 919;	roof[0][3].y1 = 569, roof[0][3].y2 = 580;	//毒液位置的头顶
	roof[0][4].x1 = 160, roof[0][4].x2 = 550;   roof[0][4].y1 = 393, roof[0][4].y2 = 408;	//转换器右边的顶
	roof[0][5].x1 = 550, roof[0][5].x2 = 948;   roof[0][5].y1 = 420, roof[0][5].y2 = 435;	//转换器那行最右边的顶
	roof[0][6].x1 = 982, roof[0][6].x2 = 1060;	roof[0][6].y1 = 460, roof[0][6].y2 = 475;	//5下边多出来的顶
	roof[0][7].x1 = 100, roof[0][7].x2 = 776;   roof[0][7].y1 = 300, roof[0][7].y2 = 315;		//左上梯形的顶
	roof[0][8].x1 = 777, roof[0][8].x2 = 948;	roof[0][8].y1 = 310, roof[0][8].y2 = 325;	//梯形右边接的平地
	roof[0][9].x1 = 277, roof[0][9].x2 = 433;   roof[0][9].y1 = 177, roof[0][9].y2 = 192;	//门那一行的左边梯形
	roof[0][10].x1 = 433, roof[0][10].x2 = 1060;	roof[0][10].y1 = 162, roof[0][10].y2 = 177;	//门下面的平顶
	roof[0][11].x1 = 0, roof[0][11].x2 = 1060;	roof[0][11].y1 = 30, roof[0][11].y2 = 45;	//全图棚顶

	 


	//左墙壁
	wallleft[0][1].y1 = 617, wallleft[0][1].y2 = 621; wallleft[0][1].x = 369;	//开始两个人夹板部右端做墙壁
	wallleft[0][2].y1 = 496, wallleft[0][2].y2 = 520; wallleft[0][2].x = 505;	//转换器右边的左墙
	wallleft[0][3].y1 = 565, wallleft[0][3].y2 = 572; wallleft[0][3].x = 919;	//毒液右边的左墙
	wallleft[0][4].y1 = 368, wallleft[0][4].y2 = 392; wallleft[0][4].x = 575;	//中间行中间位置小部分左墙
	wallleft[0][5].y1 = 297, wallleft[0][5].y2 = 313; wallleft[0][5].x = 949;	//从上到下第二行最有段边界
	wallleft[0][6].y1 = 268, wallleft[0][6].y2 = 272; wallleft[0][6].x = 235;	//第二行最左边的下边左边界
	wallleft[0][7].y1 = 240, wallleft[0][7].y2 = 260; wallleft[0][7].x = 730;	//第二行右边的梯形右边小左边界
	wallleft[0][8].y1 = 185, wallleft[0][8].y2 = 240; wallleft[0][8].x = 190;	//第二行左边的梯形右边小左边界
	wallleft[0][10].y1 = 108, wallleft[0][10].y2 = 151; wallleft[0][10].x = 400;	//门行左边的梯形右边小左边界
	 

	//右墙壁
	wallright[0][1].y1 = 667, wallright[0][1].y2 = 687;	wallright[0][1].x = 974;	//右下两节台阶
	wallright[0][7].y1 = 620, wallright[0][7].y2 = 667;	wallright[0][7].x = 1010;	
	wallright[0][2].y1 = 447, wallright[0][2].y2 = 460; wallright[0][2].x = 948;	//1上边的墙多出来的
	//wallright[0][3].y1 = 420, wallright[0][3].y2 = 423; wallright[0][3].x = 508;	//2左边多出来的小角
	wallright[0][4].y1 = 392, wallright[0][4].y2 = 396; wallright[0][4].x = 148;	//转换器控制的木板右边的陆地的左边界
	wallright[0][5].y1 = 262, wallright[0][5].y2 = 272; wallright[0][5].x = 532;	//从上到下第二行中间右边界
	wallright[0][6].y1 = 163, wallright[0][6].y2 = 180;	wallright[0][6].x = 277;	//最上面一行最左边的小右边界
	wallright[0][8].y1 = 108, wallright[0][8].y2 = 151; wallright[0][8].x = 318;	//门行左边的梯形左边小右边界
}
//判断火门
int judgefiredoor(double X, double Y)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (X + widthleft >= FIREDOORX && X + widthleft <= FIREDOORX + DOORWIDTH)
			if (Y + lengthdown <= FIREDOORY + DOORHEIGHT)
				return 1;
	}
	return 0;
}
//判断冰门
int judgeicedoor(double X, double Y)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (X + widthleft >= ICEDOORX && X + widthleft <= ICEDOORX + DOORWIDTH)
			if (Y + lengthdown <= ICEDOORY + DOORHEIGHT)
				return 1;
	}
	return 0;
}


//判断冰面
int judgeicefloor(double X, double Y)
{
	if (X + widthright >= 540 && X + widthright <= 640)
	{
		if (Y + lengthdown >= 685 && Y + lengthdown <= 713)
			return 1;
	}

	return 0;
}
//判断毒液
int judgepoisonfloor(double X, double Y)
{

	if (X + widthright >= 720 && X + widthright <= 810)
	{
		if (Y + lengthdown >= 540 && Y + lengthdown <= 568)
			return 1;
	}
	return 0;
}
int judgeswitch(double X, double Y)	//判断转换器
{
	if (X + widthright >= 310 && X + widthright <= 340)
	{
		if (Y + lengthdown >= 508 && Y + lengthdown <= 523)
			return 1;
	}

	return 0;
}
//判断火面
int judgefirefloor(double X, double Y)
{
	if (X + widthright >= 785 && X + widthright <= 870)
	{
		if (Y + lengthdown >= 685 && Y + lengthdown <= 713)
			return 1;
	}

	return 0;
}

//判断是否在地面或斜面上
int judgefloor(double X, double Y, int i, double V)
{
	for (int cnt = 0; cnt < 50; cnt++)
	{
		if (X + widthleft >= floor[i][cnt].x1 && X + widthright <= floor[i][cnt].x2 && Y + lengthdown >= floor[i][cnt].y1 && Y + lengthdown <= floor[i][cnt].y2)
			return 1;
	}
	if (V <= 0)
		for (int cnt = 50; cnt < 75; cnt++)
		{
			if (X + widthleft >= floor[i][cnt].x1 && X + widthright <= floor[i][cnt].x2 && Y + lengthdown >= floor[i][cnt].y1 && Y + lengthdown <= floor[i][cnt].y2)
				return 1;
		}
	if (V >= 0)
		for (int cnt = 75; cnt < 100; cnt++)
		{
			if (X + widthleft >= floor[i][cnt].x1 && X + widthright <= floor[i][cnt].x2 && Y + lengthdown >= floor[i][cnt].y1 && Y + lengthdown <= floor[i][cnt].y2)
				return 1;
		}
	return 0;
}
//判断是否会撞顶面
int judgeroof(double X, double Y, int i)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (X + widthright >= roof[i][cnt].x1 && X + widthleft <= roof[i][cnt].x2 && Y + lengthup >= roof[i][cnt].y1 && Y + lengthup <= roof[i][cnt].y2)
			return 1;
	}
	return 0;
}
//判断是否撞左墙
int judegewall_left(double X, double Y, int i)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (X + widthleft - wallleft[i][cnt].x <= 10 && X + widthleft - wallleft[i][cnt].x >= -40)
			if (Y + lengthup <= wallleft[i][cnt].y2 && Y + lengthdown >= wallleft[i][cnt].y1)
				return 1;
	}
	return 0;
}
//判断是否撞右墙
int judegewall_right(double X, double Y, int i)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (wallright[i][cnt].x - (X + widthright) <= 10 && wallright[i][cnt].x - (X + widthright) >= -40)
			if (Y + lengthup <= wallright[i][cnt].y2 && Y + lengthdown >= wallright[i][cnt].y1)
				return 1;
	}
	return 0;
}

void run(double* VX, double* VY, double X, double Y)
{
	if (1)    //正常地面
	{
		if (*VX > 0)
		{
			if (*VX - ax >= 0)
				*VX -= time * ax;
			else *VX = 0;
		}
		if (*VX < 0)
		{
			if (*VX + ax <= 0)
				*VX += time * ax;
			else *VX = 0;
		}
		if ((judgefloor(X, Y, 0, *VX) == 1 && (*VY < -5) || (*VY == 0)) || (judgefloor(X, Y, 0, *VX) == 0))
		{
			*VY += ay * time;
		}
		else *VY = 0;
		if ((judgeroof(X, Y, 0) == 1) && (*VY < 0))
		{
			*VY = 0;
		}
	}
}
//冰火娃在正常地面与晶体上的跑动速度与路程关系
void svrelation(double* VX, double* VY, double* X, double* Y)
{
	*X += *VX * time;
	*Y += *VY * time;
	if (*VX != 0)*Y -= 1.5;
	else *Y -= 1.0 / 6;
}
//人物图片变换
void changepeople()
{
	int modex = 0, modey = 0;
	int mode2x = 0, mode2y = 0;

	//冰娃图片切换,规定左 -1，右 1，上 1，下 -1

	if (GetAsyncKeyState('D'))
	{
		modex++;
		if (icex + widthright <= edgeright)
		{
			if (judegewall_right(icex, icey, 0) == 0)
				icevx = vx;
		}
		else icevx = 0;
	}

	if (GetAsyncKeyState('A'))
	{
		modex--;
		if (icex + widthleft >= edgeleft)
		{
			if (judegewall_left(icex, icey, 0) == 0)
				icevx = -vx;
		}
		else icevx = 0;
	}
	if (GetAsyncKeyState('W'))
	{
		modey++;

		if (judgefloor(icex, icey, barrier, icevx))
		{
			//if (judgeroof(firex, firey, 0) == 0)
			icevy = -vy;

		}
	}


	if (GetAsyncKeyState(VK_RIGHT))
	{
		mode2x++;
		if (firex + widthright <= edgeright)
		{
			if (judegewall_right(firex, firey, 0) == 0)
				firevx = vx;
		}
		else firevx = 0;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		mode2x--;
		if (firex + widthleft >= edgeleft)
		{
			if (judegewall_left(firex, firey, 0) == 0)
				firevx = -vx;
		}
		else firevx = 0;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		mode2y++;
		if (judgefloor(firex, firey, barrier, firevx))
		{
			//if (judgeroof(firex, firey, 0) == 0)
			firevy = -vy;

		}

	}



	//6个动作情况
	//冰娃图片切换,规定左 -1，右 1，上 1，下 -1
	if (modex == 0 && modey == 0)//静止战立
	{
		putimage_withalpha(NULL, _icestill, icex, icey);
	}
	if (modex == 1 && modey == 0)//向右运动
	{
		putimage_withalpha(NULL, _iceright, icex, icey);
	}
	if (modex == 1 && modey == 1)//向右上运动
	{
		putimage_withalpha(NULL, _iceru, icex, icey);
	}
	if (modex == -1 && modey == 0)//向左运动
	{
		putimage_withalpha(NULL, _iceleft, icex, icey);
	}
	if (modex == -1 && modey == 1)//向左上运动
	{
		putimage_withalpha(NULL, _icelu, icex, icey);
	}
	if (modex == 0 && modey == 1)//向上运动
	{
		putimage_withalpha(NULL, _iceup, icex, icey);
	}

	//火人
	if (mode2x == 0 && mode2y == 0)//静止战立
	{
		putimage_withalpha(NULL, _firestill, firex, firey);
	}
	if (mode2x == 1 && mode2y == 0)//向右运动
	{
		putimage_withalpha(NULL, _fireright, firex, firey);
	}
	if (mode2x == 1 && mode2y == 1)//向右上运动
	{
		putimage_withalpha(NULL, _fireru, firex, firey);
	}
	if (mode2x == -1 && mode2y == 0)//向左运动
	{
		putimage_withalpha(NULL, _fireleft, firex, firey);
	}
	if (mode2x == -1 && mode2y == 1)//向左上运动
	{
		putimage_withalpha(NULL, _firelu, firex, firey);
	}
	if (mode2x == 0 && mode2y == 1)//向上运动
	{
		putimage_withalpha(NULL, _fireup, firex, firey);
	}



}
void map1()
{
	msg = { 0 };
	for (; is_run(); delay_fps(60))
	{

		cleardevice();
		putimage(0, 0, _barrier1);		//进入游戏关卡1
		if (firedoormode && judgefiredoor(firex, firey) == 1)		
		{
			if (firedoormode > 18)
				putimage_withalpha(NULL, FIREDOOR3, FIREDOORX, FIREDOORY);
			else if (firedoormode > 12)
				putimage_withalpha(NULL, FIREDOOR2, FIREDOORX, FIREDOORY);
			else if (firedoormode > 6)
				putimage_withalpha(NULL, FIREDOOR1, FIREDOORX, FIREDOORY);
			else
				putimage_withalpha(NULL, FIREDOOR0, FIREDOORX, FIREDOORY);
			if (firedoormode > 1 && judgefiredoor(firex, firey)) firedoormode--;		//门一点点下降
		}
		if (judgefiredoor(firex, firey) == 0) firedoormode = 24;
		if (icedoormode && judgeicedoor(icex, icey) == 1)		
		{
			if (icedoormode > 18)
				putimage_withalpha(NULL, ICEDOOR3, ICEDOORX, ICEDOORY);
			else if (icedoormode > 12)
				putimage_withalpha(NULL, ICEDOOR2, ICEDOORX, ICEDOORY);
			else if (icedoormode > 6)
				putimage_withalpha(NULL, ICEDOOR1, ICEDOORX, ICEDOORY);
			else
				putimage_withalpha(NULL, ICEDOOR0, ICEDOORX, ICEDOORY);
			if (icedoormode > 1 && judgeicedoor(icex, icey)) icedoormode--;
		}
		if (judgeicedoor(icex, icey) == 0) icedoormode = 24;

		changepeople();			//冰火人动作的配置
		run(&firevx, &firevy, firex, firey);		//移动的速度判定
		run(&icevx, &icevy, icex, icey);
		svrelation(&firevx, &firevy, &firex, &firey);	//路程和速度判定
		svrelation(&icevx, &icevy, &icex, &icey);
		putimage_withalpha(NULL, SWITCH, 260, 460);		//转换器的图片
		putimage_withalpha(NULL, lift, 30, lifty);		//升降台
		if (judgeicedoor(icex, icey) && judgefiredoor(firex, firey))	//成功
		{
			while (1)
			{
				while (mousemsg())
				{
					msg = getmouse();
				}
				if (msg.msg == 16)return;
				putimage(0, 0, succeeded);

				datainitial();
			}

		}
		if (judgeswitch(firex, firey) + judgeswitch(icex, icey) > 0 && lifty <= 450)	//转换器控制
		{
			floor[0][15].y1++; floor[0][15].y2++; lifty++;
		}
		if (judgeicefloor(firex, firey) || judgepoisonfloor(firex, firey) || judgepoisonfloor(icex, icey) || judgefirefloor(icex, icey))//死亡判定
		{
			while (1)
			{
				while (mousemsg())
				{
					msg = getmouse();
				}
				if (msg.msg == 16)return;
				putimage(0, 0, _dead);

				datainitial();
			}

		}

	}
}
//游戏主地图界面
void mapmain()
{
	msg = { 0 };
	while (1)
	{
		for (; msg.msg != 16; delay_fps(60))
		{
			while (mousemsg())
			{
				msg = getmouse();
			}

			putimage(0, 0, _back1);	//地图

		}
		map1();
		msg = { 0 };
	}

}
void explanation()
{
	msg = { 0 };
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			msg = getmouse();
		}
		putimage(0, 0, _explanation);	//地图界面
		if (msg.flags == 1) return;		
	}
}
//关于我们游戏界面
void about()
{
	msg = { 0 };
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			msg = getmouse();
		}
		putimage(0, 0, _back2);		//开发者信息
		if (msg.flags == 1) return;
	}
}
//加载进入界面，地图，游戏关卡背景
void welcome()
{
	msg = { 0 };
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			msg = getmouse();
		}
		cleardevice();
		putimage(0, 0, _enter);			//引入进入主界面，左上角0,0处开始
		if (msg.x >= 425 && msg.x <= 645)
		{
			if (msg.y >= 430 && msg.y <= 480)	//开始按钮的位置
			{
				putimage_withalpha(NULL, _start, 380, 405);		//贴上一个大一号的开始按钮
				if (msg.flags == 1)		//点击进入地图
				{
					mapmain();		//地图页面
				}
			}
			else if (msg.y >= 540 && msg.y <= 590)	//游戏说明按钮位置
			{
				putimage_withalpha(NULL, _explanationbt, 385, 517);	//贴上一个大一号的游戏说明
				if (msg.flags == 1)
				{
					explanation(); //游戏说明页面
					//msg = { 0 };
				}

			}
			else if (msg.y >= 650 && msg.y <= 700)
			{
				putimage_withalpha(NULL, _about, 380, 623);	//贴上一个开发人员的按钮
				if (msg.flags == 1)
				{
					about();		//开发人员页面
				}	
			}
		}
	}
}
//控制台函数，调节逻辑关系
void operate()
{
	firex = initial_firex[0];
	firey = initial_firey[0];		//火娃的坐标
	icex = initial_icex[0];
	icey = initial_icey[0];			//冰娃的坐标
	msg = { 0 };

	for (; is_run(); delay_fps(60))	//ege帧率循环，一秒60帧
	{
		while (mousemsg())
		{
			msg = getmouse();
		}
		cleardevice();
		welcome();

	}
}
int main()
{
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	/*函数指针*/
	typedef void(*Funp)(void);
	/*加载动态库*/
	HMODULE hmodule = LoadLibrary("Login");
	/*如果调用成功*/
	if (hmodule)
	{
		/*获取函数*/
		Funp dll_func = (Funp)GetProcAddress(hmodule, TEXT("myfunc"));
		/*判断函数执行*/

		if (dll_func != NULL)
		{
			//cout << "dll加载成功！" << endl;
			dll_func();
		}
		else
		{
			//	cout << "无法找到DLL" << endl;
		}

		/*释放函数库*/

		FreeLibrary(hmodule);
	}
	else
	{
		//	cout << "加载失败！" << endl;
	}



	initgraph(1100, 740);
	setcaption("森林冰火人");
	initial();
	//	mouse();
	operate();
	return 0;
}
