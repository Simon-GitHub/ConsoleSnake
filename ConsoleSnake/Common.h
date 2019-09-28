//************************************************************
//���ļ������궨�塢ȫ�ֳ�����ö�����ͺ�ȫ�ֺ����Ķ���
//************************************************************
#pragma once
#include<Windows.h>
#include<conio.h>

//���幦�ܼ�
#define UP_KEY (-1)			//�����Ϸ����
#define DOWN_KEY (-2)		//�����·����
#define LEFT_KEY (-3)		//���������
#define RIGHT_KEY (-4)		//�����ҷ����
//�����ַ���
#define PAUSE_KEY 13			//������ͣ��
#define ESC_KEY 27		//�����˳�������esc���˳���
#define ENTER_KEY 13		//����س���

#define BOARD_X 1
#define BOARD_Y 3
#define WIDTH 30
#define HIGHT 23

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum Color
{
	BLACK = 0,
	GRAY = 8,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};


//��ȡһ���������밴�������䷵��
int GetKey()
{
	int key{ _getch() };
	if (key == 0xE0 || key == 0)		//�����õİ���ֵΪ0x0E��0���ʾ�����˹��ܼ�
	{
		switch (_getch())		//�����˹��ܼ���Ҫ�ٴε���_getch����
		{
			case 72: key = UP_KEY; break;
			case 80: key = DOWN_KEY; break;
			case 75: key = LEFT_KEY; break;
			case 77: key = RIGHT_KEY; break;
			default: break;
		}
	}
	if (key>='a' && key<='z')		//���������Сд��ĸ�����Զ�ת���ɴ�д��ĸ
		key -= 32;
	return key;
}

//ΪSYSTEMTIME�ṹ���ؼ������������ȷ��a>b������·�������ʱ���ĺ����������Ƿ��ص�ֵ���ᳬ��3000����
int operator-(SYSTEMTIME a, SYSTEMTIME b)
{
	if (a.wSecond == b.wSecond)
		return a.wMilliseconds - b.wMilliseconds;
	else if (a.wSecond - b.wSecond == 1 || a.wSecond - b.wSecond == -59)
		return a.wMilliseconds - b.wMilliseconds + 1000;
	else
		return a.wMilliseconds - b.wMilliseconds + 2000;
}

template<class T>
T Min3(T v1, T v2, T v3)
{
    T min = v1;
    if (v2 < min)
        min = v2;
    if (v3 < min)
        min = v3;
    return min;
}

template<class T>
T Max3(T v1, T v2, T v3)
{
    T max = v1;
    if (v2 > max)
        max = v2;
    if (v3 > max)
        max = v3;
    return max;
}
