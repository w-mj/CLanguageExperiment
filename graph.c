#include "graph.h"
#include "console.h"
#include "conio.h"
#include "kbio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void drawRect(int x, int y, int w, int h, bool fill)
{
    gotoxy(x, y);
    printf("��");
    for (int i = 0; i < w - 2; i++)
        printf("��");
    printf("��");
    for (int i = 1; i < h - 1; i++) {
        gotoxy(x, y + i);
        printf("��");
        if (fill) {
            for (int i = 0; i < w - 2 ; i++)
                printf("  ");
            printf("��");
        }
        else {
            gotoxy(x + w -1 , y + i);
            printf("��");
        }
    }
    gotoxy(x, y + h - 1);
    printf("��");
    for (int i = 0; i < w - 2; i++)
        printf("��");
    printf("��");
}

void message(const char * context)
{
    setColor(0x9f);
    gotoxy(0, 29);
    printf("%s", context);
}

void errorMsg(const char * context)
{
    gotoxy(0, 29);
    setTempColor(0xc0);
    printf("%s", context);
    resumeColor();
}

void msgLine(int x, int y, const char * text)
{
    gotoxy(x, y);
    while (*text != '\0') {
        if (*text == '\n')
            gotoxy(x, ++y);
        else
            printf("%c", *text);
        text++;
    }
}

inputBox createInputBox(int x, int y, enum StringType type, char * target, int length)
{
    inputBox ans = (inputBox)malloc(sizeof(struct INPUTBOX));
    ans -> x = x;
    ans -> y = y;
    ans -> owned = 0;
    ans -> type = type;
    ans -> length = length;
    ans -> target = target;
    return ans;
}
void setAlreadySelected(choiceBox cb)
{
    cb -> alreadySelected = true;
}

int input(inputBox box)
{
    int ret;
    gotoxy(box -> x + box -> owned, box -> y);
    ret = getString(box -> target, box -> type, box -> owned, box -> length);
    box -> owned = strlen(box -> target);
    return ret;
}

void destroyInputBox(inputBox box)
{
    free(box);
}

choiceBox createChoiceBox(int x, int y, unsigned short normalColor, unsigned short choosenColor, const char *text)
{
    choiceBox ret = (choiceBox)malloc(sizeof(struct CHOICEBOX));
    ret -> x = x;
    ret -> y = y;
    ret -> normalColor = normalColor;
    ret -> choosenColor = choosenColor;
    ret -> choosen = false;
    ret -> alreadySelected = false;
    ret -> focusOn = true;
    strcpy(ret -> context, text);
    return ret;
}

void showChoiceBox(choiceBox cb)
{
    gotoxy(cb -> x, cb -> y);
    if (cb -> alreadySelected) {
        setColor(cb -> focusOn? cb -> normalColor: (cb -> normalColor) | 0x07);
        printf("��%s", cb -> context);
    }
    if (cb -> choosen) {
        setColor(cb -> focusOn? cb -> choosenColor: (cb -> choosenColor) | 0x07);
        printf("��%s", cb -> context);
    } else  {
        setColor(cb -> focusOn? cb -> normalColor: (cb -> normalColor) | 0x07);
        printf("��%s", cb -> context);
    }
}

void changeStatus(choiceBox cb)
{
    cb -> choosen = ! cb -> choosen;
}

void setSelect(choiceBox cb)
{
    cb -> choosen = true;
}

void clearSelect(choiceBox cb)
{
    cb -> choosen = false;
}

void destroyChoiceBox(choiceBox cb)
{
    free(cb);
}

int rectMap[60][30];

void addMap(int * a, int b)
{
    *a = (*a) | b;
}
void clearRectMap(void)
{
    memset(rectMap, 0, sizeof(rectMap));
}
/* ����λ�ֱ��ʾ�ϡ��¡����� */
/*       ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� */
/* 0 10 0C 03 06 09 0A 05 0E 0B 0D 07 0F*/
/* 0Ϊ�����ڣ�10Ϊ�����ڲ� */
void setArect(int x, int y, int w, int h)
{
    int cx = x, cy = y;
    if (w & h == 0 || w == 1 && h == 1)
        return;

    if (w == 1) {
        addMap(&rectMap[cx][cy++], 0x04);
        while (cy <= h - 2)
            addMap(&rectMap[cx][cy++], 0x0C);
        addMap(&rectMap[cx][cy++], 0x08);
    } else if (h == 1) {
        addMap(&rectMap[cx++][cy], 0x01);
        while (cx <= w - 2)
            addMap(&rectMap[cx++][cy], 0x03);
        addMap(&rectMap[cx++][cy], 0x02);
    } else {

        addMap(&rectMap[cx++][cy], 0x05);
        for (int i = 0; i < w - 2; i++)
            addMap(&rectMap[cx++][cy], 0x03);
        addMap(&rectMap[cx++][cy], 0x06);
        cx = x;
        for (int i = 1; i < h - 1; i++) {
            cy = y + i;
            cx = x;
            addMap(&rectMap[cx++][cy], 0x0C);
            for (int j = 0; j < w - 2 ; j++)
                addMap(&rectMap[cx++][cy], 0x10);
            addMap(&rectMap[cx++][cy], 0x0C);
        }
        cy = y + h - 1;
        cx = x;
        addMap(&rectMap[cx++][cy], 0x09);
        for (int i = 0; i < w - 2; i++)
            addMap(&rectMap[cx++][cy], 0x03);
        addMap(&rectMap[cx++][cy], 0x0A);
    }
/*
    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 60; x++) {
            printf("%x", rectMap[x][y]);
        }
        printf("\n");
    }
*/
}

void drawMultipleRect(void)
{
    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 60; x ++) {
            if (rectMap[x][y] == 0)
                continue;
            if (x == 0 || rectMap[x - 1][y] == 0)
                gotoxy(x*2, y);
            if (rectMap[x][y] == 0x10) {
                printf("  ");
                continue;
            }
            switch(rectMap[x][y] & 0x0f)
            {
                case 0x0C:
                case 0x04:
                case 0x08:
                    printf("��");
                    break;
                case 0x03:
                case 0x01:
                case 0x02:
                    printf("��");
                    break;
                case 0x06:
                    printf("��");
                    break;
                case 0x09:
                    printf("��");
                    break;
                case 0x0A:
                    printf("��");
                    break;
                case 0x05:
                    printf("��");
                    break;
                case 0x0E:
                    printf("��");
                    break;
                case 0x0B:
                    printf("��");
                    break;
                case 0x0D:
                    printf("��");
                    break;
                case 0x07:
                    printf("��");
                    break;
                case 0x0F:
                    printf("��");
                    break;
                default:
                    fprintf(stderr, "WRROR-tk%xtk\n", rectMap[x][y]);
/*       ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� */
/* 0 f0 0C 03 06 09 0A 05 0E 0B 0D 07 0F*/
            }
        }
    }

}


void msgBox(int x, int y, int w, int h, const char *text)
{
    gotoxy(x, y);
    int countLine = 1;
    int countColumn = 0;
    while (*text != '\0') {
        if (*text == '\n' || (countColumn == w && (!(countColumn & 1)))) {
            if (countLine == h)
                break;
            else {
                gotoxy(x, ++y);
                countLine++;
                countColumn = 0;
            }
        }

            printf("%c", *text);
        text++;
        countColumn++;
    }
}

void clearInputBox(inputBox box)
{
    gotoxy(box->x, box->y);
    printf("%*s", box->length, "");
    box -> owned = 0;
}

void focusOff(choiceBox cb[], int n)
{
    for (int i = 0; i < n; i++) {
        cb[i] -> focusOn = false;
    }
}
void focusOn(choiceBox cb[], int n)
{
    for (int i = 0; i < n; i++) {
        cb[i] -> focusOn = true;
    }
}
