//************************************************************
//				���ļ�Ϊ����̨���ȫ�ֺ����Ķ���
//************************************************************
#pragma once
#include<Windows.h>
#include"Common.h"

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

//����һ�����ֽ��ַ����ĳ���ռ�õİ���ַ���
size_t WcharStrHalfWidthLen(const wchar_t* str)
{
	size_t size{ 0 };
	const size_t length{ wcslen(str) };
	for (int i{ 0 }; i < length; i++)
	{
		if (str[i] >= 0 && str[i] < 128)
			size++;		//���һ��Unicode�ַ�������0~127��Χ�ڣ���ռһ������ַ����
		else
			size += 2;		//������ռ��������ַ����
	}
	return size;
}

//��x,y���괦��һ������
void PrintCell(short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	WriteConsoleOutputCharacterW(handle, L"��", 1, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);
}

//�ڽ����x,y���괦���һ������
void PrintInt(int num, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	wchar_t str[20];
	_itow_s(num, str, 10);
	size_t len{ wcslen(str) };
	WriteConsoleOutputCharacterW(handle, str, len, pos, &unuse);		//����ַ�
	FillConsoleOutputAttribute(handle, color, len, pos, &unuse);		//������ɫ
}

//�ڽ����x,y���괦���һ���ַ���
void PrintString(const wchar_t *str, short x, short y, Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	size_t len{ wcslen(str) };
	size_t len_halfwidth{ WcharStrHalfWidthLen(str) };	//�ַ���ռ�ð���ַ���
	WriteConsoleOutputCharacterW(handle, str, len, pos, &unuse);
	FillConsoleOutputAttribute(handle, color, len_halfwidth, pos, &unuse);		//������ɫ
}

//�������̨��x,y����ʼ��length���ַ�
void ClearString(short x, short y, size_t length)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	FillConsoleOutputAttribute(handle, BLACK, length, pos, &unuse);
}

//����ƶ���x,y����
void GotoXY(short x, short y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//��ʾ�����ع��
void CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = visible;
	cci.dwSize = 25;		//����ȣ�ȡֵΪ1~100
	SetConsoleCursorInfo(handle, &cci);
}
