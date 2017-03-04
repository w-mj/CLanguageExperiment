#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "console.h"

HANDLE hConsole = NULL;

void initConsole(void)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == NULL) {
        fprintf(stderr, "��ʼ�������޷���ȡ����̨���\n");
        exit(1);
    }
    SetConsoleTitle("ѡ��ϵͳ");
    COORD size = {120, 9001};  // ���ÿ���̨����
    SetConsoleScreenBufferSize(hConsole,size);
    SMALL_RECT rc =  {0, 0, 119, 29};  // ��������ֵΪ��������1
    SetConsoleWindowInfo(hConsole, true, &rc);
    char tt[1000];
    getcwd(tt, 1000);
    fputs(tt, stderr);
}

void gotoxy(int x, int y)
{
  COORD scrn;
  scrn.X = x; scrn.Y = y;
  SetConsoleCursorPosition(hConsole,scrn);
}

void setColor(unsigned short int color)
{
    SetConsoleTextAttribute(hConsole,color);
    LastColor = color;
}

void setTempColor(unsigned short color)
{
    SetConsoleTextAttribute(hConsole,color);
}

void resumeColor(void)
{
    SetConsoleTextAttribute(hConsole, LastColor);
}

void clearColor(void)
{
    setColor(0x0f);
    LastColor = 0x0f;
}

void clearScreen(void)
{
    system("cls");
    //COORD coord={0,0};
    //SetConsoleCursorPosition(hConsole, coord);
}

void hideCursor(void)
{
    CONSOLE_CURSOR_INFO a = {1, 0};
    SetConsoleCursorInfo(hConsole, &a);
}

void showCursor(void)
{
    CONSOLE_CURSOR_INFO a = {100, 1};
    SetConsoleCursorInfo(hConsole, &a);
}

void destroyConsole(void)
{
    CloseHandle(hConsole);
}
