#include<stdio.h>
#include<windows.h>
#include<graphics.h>   //�����ϵ�һϵ�в���
#include<time.h>	//�и���ʱ�亯��
#include<conio.h>	//��������
#include<mmSystem.h>   //��������
#pragma comment (lib,"winmm.lib")	//����winmm.lib��

//��Һ��ˮƽ720��800���߶�540��568
//������ˮƽ560��610���¸߶�685����
//������790��850
// ת������ˮƽ301��337����ֱ508��523��
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

#define time 1.0/60		//ʱ��
#define widthleft 43	//����	x+widthleft��С�����
#define widthright 55	//�ҿ��	x+widthright��С���ұ߽�
#define lengthup 30		//�ϸ߶�
#define lengthdown 77	//�¸߶�

#define edgeleft 50		//���Ե
#define edgeright 1050	//�ұ�Ե
#define DOORWIDTH 60	//�ſ�
#define DOORHEIGHT 123	//�Ÿ�
#define ICEDOORX 875	
#define ICEDOORY 75		//����λ�����½�λ��
#define FIREDOORX 950
#define FIREDOORY 75	//����λ�����½�λ��

#define vx 260		//ˮƽ�ٶ�
#define vy 500		//��ֱ�ٶ�
#define ax 250		//ˮƽ���ٶ�
#define ay 1200		//��ֱ���ٶ�

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

//�������꣬����һ����������3�أ�ÿ�ؿ�����100�����������
typedef struct model1		//����
{
	int x1 = 0, x2 = 1100, y1 = 699, y2 = 714;//714
}model1_;
model1_ floor[3][100], roof[3][100];
typedef struct model2		//ǽ��
{
	int x = 369, y1 = 617, y2 = 621;
}model2_;
model2_ wallleft[3][100], wallright[3][100];

void datainitial()	//���ݳ�ʼ��
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
	//��ʼ��ͼƬ
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

	getimage(succeeded, "pictures//�ɹ�.jpg");
	getimage(_dead, "pictures//����.jpg");
	getimage(_explanation, "pictures//��Ϸ˵��.jpg");
	getimage(lift, "pictures//����̨.png");
	getimage(SWITCH, "pictures//�������.png");
	getimage(_enter, "pictures//�������.jpg");
	getimage(_back1, "pictures//��ͼ.jpg");
	getimage(_barrier1, "pictures//��Ϸ�ؿ�1.png");
	getimage(_back2, "pictures//�������ǵ���Ϸ.jpg");
	getimage(_start, "pictures//��ʼ��ť.png");
	getimage(_explanationbt, "pictures//��Ϸ˵��.png");
	getimage(_about, "pictures//��������.png");
	getimage(_icestill, "pictures//���޾�.png");
	getimage(_iceup, "pictures//������.png");
	getimage(_icedown, "pictures//������.png");
	getimage(_iceright, "pictures//������.png");
	getimage(_iceleft, "pictures//������.png");
	getimage(_icelu, "pictures//��������.png");
	getimage(_iceru, "pictures//��������.png");
	getimage(_iceld, "pictures//��������.png");
	getimage(_icerd, "pictures//��������.png");
	getimage(_firestill, "pictures//���޾�.png");
	getimage(_fireup, "pictures//������.png");
	getimage(_firedown, "pictures//������.png");
	getimage(_fireright, "pictures//������.png");
	getimage(_fireleft, "pictures//������.png");
	getimage(_firelu, "pictures//��������.png");
	getimage(_fireru, "pictures//��������.png");
	getimage(_fireld, "pictures//��������.png");
	getimage(_firerd, "pictures//��������.png");
	getimage(FIREDOOR0, "pictures//����0.png");
	getimage(FIREDOOR1, "pictures//����1.png");
	getimage(FIREDOOR2, "pictures//����2.png");
	getimage(FIREDOOR3, "pictures//����3.png");
	getimage(FIREDOOR4, "pictures//����4.png");
	getimage(ICEDOOR0, "pictures//����0.png");
	getimage(ICEDOOR1, "pictures//����1.png");
	getimage(ICEDOOR2, "pictures//����2.png");
	getimage(ICEDOOR3, "pictures//����3.png");
	getimage(ICEDOOR4, "pictures//����4.png");

	//�ذ������
	floor[0][1].x1 = 36, floor[0][1].x2 = 369;		floor[0][1].y1 = 605, floor[0][1].y2 = 620;		//���˳�ʼ�ذ�
	floor[0][2].x1 = 974, floor[0][2].x2 = 1060;	floor[0][2].y1 = 655, floor[0][2].y2 = 670;		//���½�������ƽ̨
	floor[0][3].x1 = 1019, floor[0][3].x2 = 1060;	floor[0][3].y1 = 609, floor[0][3].y2 = 624;		//���½���ƽ̨
	floor[0][4].x1 = 36, floor[0][4].x2 = 505;		floor[0][4].y1 = 508, floor[0][4].y2 = 523;		//��Һ�������ߵĵ���
	floor[0][5].x1 = 446, floor[0][5].x2 = 919;		floor[0][5].y1 = 553, floor[0][5].y2 = 568;		//��Һ���е���
	floor[0][6].x1 = 148, floor[0][6].x2 = 575;		floor[0][6].y1 = 380, floor[0][6].y2 = 395;		//ת��������˵ĵ���
	floor[0][7].x1 = 508, floor[0][7].x2 = 1060;	floor[0][7].y1 = 408, floor[0][7].y2 = 423;		//ת�������Ҷ˵ĵ���
	floor[0][8].x1 = 36, floor[0][8].x2 = 190;		floor[0][8].y1 = 196, floor[0][8].y2 = 211;		//���ϵ��µ�2���������ϵ���???
	floor[0][16].x1 = 179, floor[0][16].x2 = 240;	floor[0][16].y1 = 240, floor[0][16].y2 = 250;		//���ϵ��µ�2���������ұߵ���
	floor[0][9].x1 = 200, floor[0][9].x2 = 949;		floor[0][9].y1 = 284, floor[0][9].y2 = 299;		//�ӵ�2����������Ҷ�һֱ�����ұߵ���
	floor[0][10].x1 = 532, floor[0][10].x2 = 730;	floor[0][10].y1 = 250, floor[0][10].y2 = 265;	//��2���м�ͻ����һ��ƽ��
	//floor[0][11].x1 = 277, floor[0][11].x2 = 430;	floor[0][11].y1 = 151, floor[0][11].y2 = 166;	//����һ����������±߽�
	floor[0][12].x1 = 318, floor[0][12].x2 = 393;	floor[0][12].y1 = 108, floor[0][12].y2 = 123;	//����һ����������ϱ߽�
	floor[0][13].x1 = 277, floor[0][13].x2 = 1060;	floor[0][13].y1 = 151, floor[0][13].y2 = 166;	//�ŵĴ����
	//floor[0][14].x1 = 0, floor[0][14].x2 = 190;		floor[0][14].y1 = 196, floor[0][14].y2 = 211;	//�ڶ����������
	floor[0][15].x1 = 10, floor[0][15].x2 = 150;	floor[0][15].y1 = 368, floor[0][15].y2 = 383;	//ת����ľ��



	//����
	roof[0][1].x1 = 64, roof[0][1].x2 = 369;	roof[0][1].y1 = 618, roof[0][1].y2 = 633;	//��������ʼλ�õı�ͷ��
	roof[0][2].x1 = 64, roof[0][2].x2 = 505;	roof[0][2].y1 = 516, roof[0][2].y2 = 534;	//��ʼλ�û���ͷ��
	roof[0][3].x1 = 446, roof[0][3].x2 = 919;	roof[0][3].y1 = 569, roof[0][3].y2 = 580;	//��Һλ�õ�ͷ��
	roof[0][4].x1 = 160, roof[0][4].x2 = 550;   roof[0][4].y1 = 393, roof[0][4].y2 = 408;	//ת�����ұߵĶ�
	roof[0][5].x1 = 550, roof[0][5].x2 = 948;   roof[0][5].y1 = 420, roof[0][5].y2 = 435;	//ת�����������ұߵĶ�
	roof[0][6].x1 = 982, roof[0][6].x2 = 1060;	roof[0][6].y1 = 460, roof[0][6].y2 = 475;	//5�±߶�����Ķ�
	roof[0][7].x1 = 100, roof[0][7].x2 = 776;   roof[0][7].y1 = 300, roof[0][7].y2 = 315;		//�������εĶ�
	roof[0][8].x1 = 777, roof[0][8].x2 = 948;	roof[0][8].y1 = 310, roof[0][8].y2 = 325;	//�����ұ߽ӵ�ƽ��
	roof[0][9].x1 = 277, roof[0][9].x2 = 433;   roof[0][9].y1 = 177, roof[0][9].y2 = 192;	//����һ�е��������
	roof[0][10].x1 = 433, roof[0][10].x2 = 1060;	roof[0][10].y1 = 162, roof[0][10].y2 = 177;	//�������ƽ��
	roof[0][11].x1 = 0, roof[0][11].x2 = 1060;	roof[0][11].y1 = 30, roof[0][11].y2 = 45;	//ȫͼ�ﶥ

	 


	//��ǽ��
	wallleft[0][1].y1 = 617, wallleft[0][1].y2 = 621; wallleft[0][1].x = 369;	//��ʼ�����˼а岿�Ҷ���ǽ��
	wallleft[0][2].y1 = 496, wallleft[0][2].y2 = 520; wallleft[0][2].x = 505;	//ת�����ұߵ���ǽ
	wallleft[0][3].y1 = 565, wallleft[0][3].y2 = 572; wallleft[0][3].x = 919;	//��Һ�ұߵ���ǽ
	wallleft[0][4].y1 = 368, wallleft[0][4].y2 = 392; wallleft[0][4].x = 575;	//�м����м�λ��С������ǽ
	wallleft[0][5].y1 = 297, wallleft[0][5].y2 = 313; wallleft[0][5].x = 949;	//���ϵ��µڶ������жα߽�
	wallleft[0][6].y1 = 268, wallleft[0][6].y2 = 272; wallleft[0][6].x = 235;	//�ڶ�������ߵ��±���߽�
	wallleft[0][7].y1 = 240, wallleft[0][7].y2 = 260; wallleft[0][7].x = 730;	//�ڶ����ұߵ������ұ�С��߽�
	wallleft[0][8].y1 = 185, wallleft[0][8].y2 = 240; wallleft[0][8].x = 190;	//�ڶ�����ߵ������ұ�С��߽�
	wallleft[0][10].y1 = 108, wallleft[0][10].y2 = 151; wallleft[0][10].x = 400;	//������ߵ������ұ�С��߽�
	 

	//��ǽ��
	wallright[0][1].y1 = 667, wallright[0][1].y2 = 687;	wallright[0][1].x = 974;	//��������̨��
	wallright[0][7].y1 = 620, wallright[0][7].y2 = 667;	wallright[0][7].x = 1010;	
	wallright[0][2].y1 = 447, wallright[0][2].y2 = 460; wallright[0][2].x = 948;	//1�ϱߵ�ǽ�������
	//wallright[0][3].y1 = 420, wallright[0][3].y2 = 423; wallright[0][3].x = 508;	//2��߶������С��
	wallright[0][4].y1 = 392, wallright[0][4].y2 = 396; wallright[0][4].x = 148;	//ת�������Ƶ�ľ���ұߵ�½�ص���߽�
	wallright[0][5].y1 = 262, wallright[0][5].y2 = 272; wallright[0][5].x = 532;	//���ϵ��µڶ����м��ұ߽�
	wallright[0][6].y1 = 163, wallright[0][6].y2 = 180;	wallright[0][6].x = 277;	//������һ������ߵ�С�ұ߽�
	wallright[0][8].y1 = 108, wallright[0][8].y2 = 151; wallright[0][8].x = 318;	//������ߵ��������С�ұ߽�
}
//�жϻ���
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
//�жϱ���
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


//�жϱ���
int judgeicefloor(double X, double Y)
{
	if (X + widthright >= 540 && X + widthright <= 640)
	{
		if (Y + lengthdown >= 685 && Y + lengthdown <= 713)
			return 1;
	}

	return 0;
}
//�ж϶�Һ
int judgepoisonfloor(double X, double Y)
{

	if (X + widthright >= 720 && X + widthright <= 810)
	{
		if (Y + lengthdown >= 540 && Y + lengthdown <= 568)
			return 1;
	}
	return 0;
}
int judgeswitch(double X, double Y)	//�ж�ת����
{
	if (X + widthright >= 310 && X + widthright <= 340)
	{
		if (Y + lengthdown >= 508 && Y + lengthdown <= 523)
			return 1;
	}

	return 0;
}
//�жϻ���
int judgefirefloor(double X, double Y)
{
	if (X + widthright >= 785 && X + widthright <= 870)
	{
		if (Y + lengthdown >= 685 && Y + lengthdown <= 713)
			return 1;
	}

	return 0;
}

//�ж��Ƿ��ڵ����б����
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
//�ж��Ƿ��ײ����
int judgeroof(double X, double Y, int i)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (X + widthright >= roof[i][cnt].x1 && X + widthleft <= roof[i][cnt].x2 && Y + lengthup >= roof[i][cnt].y1 && Y + lengthup <= roof[i][cnt].y2)
			return 1;
	}
	return 0;
}
//�ж��Ƿ�ײ��ǽ
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
//�ж��Ƿ�ײ��ǽ
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
	if (1)    //��������
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
//�����������������뾧���ϵ��ܶ��ٶ���·�̹�ϵ
void svrelation(double* VX, double* VY, double* X, double* Y)
{
	*X += *VX * time;
	*Y += *VY * time;
	if (*VX != 0)*Y -= 1.5;
	else *Y -= 1.0 / 6;
}
//����ͼƬ�任
void changepeople()
{
	int modex = 0, modey = 0;
	int mode2x = 0, mode2y = 0;

	//����ͼƬ�л�,�涨�� -1���� 1���� 1���� -1

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



	//6���������
	//����ͼƬ�л�,�涨�� -1���� 1���� 1���� -1
	if (modex == 0 && modey == 0)//��ֹս��
	{
		putimage_withalpha(NULL, _icestill, icex, icey);
	}
	if (modex == 1 && modey == 0)//�����˶�
	{
		putimage_withalpha(NULL, _iceright, icex, icey);
	}
	if (modex == 1 && modey == 1)//�������˶�
	{
		putimage_withalpha(NULL, _iceru, icex, icey);
	}
	if (modex == -1 && modey == 0)//�����˶�
	{
		putimage_withalpha(NULL, _iceleft, icex, icey);
	}
	if (modex == -1 && modey == 1)//�������˶�
	{
		putimage_withalpha(NULL, _icelu, icex, icey);
	}
	if (modex == 0 && modey == 1)//�����˶�
	{
		putimage_withalpha(NULL, _iceup, icex, icey);
	}

	//����
	if (mode2x == 0 && mode2y == 0)//��ֹս��
	{
		putimage_withalpha(NULL, _firestill, firex, firey);
	}
	if (mode2x == 1 && mode2y == 0)//�����˶�
	{
		putimage_withalpha(NULL, _fireright, firex, firey);
	}
	if (mode2x == 1 && mode2y == 1)//�������˶�
	{
		putimage_withalpha(NULL, _fireru, firex, firey);
	}
	if (mode2x == -1 && mode2y == 0)//�����˶�
	{
		putimage_withalpha(NULL, _fireleft, firex, firey);
	}
	if (mode2x == -1 && mode2y == 1)//�������˶�
	{
		putimage_withalpha(NULL, _firelu, firex, firey);
	}
	if (mode2x == 0 && mode2y == 1)//�����˶�
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
		putimage(0, 0, _barrier1);		//������Ϸ�ؿ�1
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
			if (firedoormode > 1 && judgefiredoor(firex, firey)) firedoormode--;		//��һ����½�
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

		changepeople();			//�����˶���������
		run(&firevx, &firevy, firex, firey);		//�ƶ����ٶ��ж�
		run(&icevx, &icevy, icex, icey);
		svrelation(&firevx, &firevy, &firex, &firey);	//·�̺��ٶ��ж�
		svrelation(&icevx, &icevy, &icex, &icey);
		putimage_withalpha(NULL, SWITCH, 260, 460);		//ת������ͼƬ
		putimage_withalpha(NULL, lift, 30, lifty);		//����̨
		if (judgeicedoor(icex, icey) && judgefiredoor(firex, firey))	//�ɹ�
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
		if (judgeswitch(firex, firey) + judgeswitch(icex, icey) > 0 && lifty <= 450)	//ת��������
		{
			floor[0][15].y1++; floor[0][15].y2++; lifty++;
		}
		if (judgeicefloor(firex, firey) || judgepoisonfloor(firex, firey) || judgepoisonfloor(icex, icey) || judgefirefloor(icex, icey))//�����ж�
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
//��Ϸ����ͼ����
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

			putimage(0, 0, _back1);	//��ͼ

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
		putimage(0, 0, _explanation);	//��ͼ����
		if (msg.flags == 1) return;		
	}
}
//����������Ϸ����
void about()
{
	msg = { 0 };
	for (; is_run(); delay_fps(60))
	{
		while (mousemsg())
		{
			msg = getmouse();
		}
		putimage(0, 0, _back2);		//��������Ϣ
		if (msg.flags == 1) return;
	}
}
//���ؽ�����棬��ͼ����Ϸ�ؿ�����
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
		putimage(0, 0, _enter);			//������������棬���Ͻ�0,0����ʼ
		if (msg.x >= 425 && msg.x <= 645)
		{
			if (msg.y >= 430 && msg.y <= 480)	//��ʼ��ť��λ��
			{
				putimage_withalpha(NULL, _start, 380, 405);		//����һ����һ�ŵĿ�ʼ��ť
				if (msg.flags == 1)		//��������ͼ
				{
					mapmain();		//��ͼҳ��
				}
			}
			else if (msg.y >= 540 && msg.y <= 590)	//��Ϸ˵����ťλ��
			{
				putimage_withalpha(NULL, _explanationbt, 385, 517);	//����һ����һ�ŵ���Ϸ˵��
				if (msg.flags == 1)
				{
					explanation(); //��Ϸ˵��ҳ��
					//msg = { 0 };
				}

			}
			else if (msg.y >= 650 && msg.y <= 700)
			{
				putimage_withalpha(NULL, _about, 380, 623);	//����һ��������Ա�İ�ť
				if (msg.flags == 1)
				{
					about();		//������Աҳ��
				}	
			}
		}
	}
}
//����̨�����������߼���ϵ
void operate()
{
	firex = initial_firex[0];
	firey = initial_firey[0];		//���޵�����
	icex = initial_icex[0];
	icey = initial_icey[0];			//���޵�����
	msg = { 0 };

	for (; is_run(); delay_fps(60))	//ege֡��ѭ����һ��60֡
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
	/*����ָ��*/
	typedef void(*Funp)(void);
	/*���ض�̬��*/
	HMODULE hmodule = LoadLibrary("Login");
	/*������óɹ�*/
	if (hmodule)
	{
		/*��ȡ����*/
		Funp dll_func = (Funp)GetProcAddress(hmodule, TEXT("myfunc"));
		/*�жϺ���ִ��*/

		if (dll_func != NULL)
		{
			//cout << "dll���سɹ���" << endl;
			dll_func();
		}
		else
		{
			//	cout << "�޷��ҵ�DLL" << endl;
		}

		/*�ͷź�����*/

		FreeLibrary(hmodule);
	}
	else
	{
		//	cout << "����ʧ�ܣ�" << endl;
	}



	initgraph(1100, 740);
	setcaption("ɭ�ֱ�����");
	initial();
	//	mouse();
	operate();
	return 0;
}
