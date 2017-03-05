#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdbool.h>
#include "kbio.h"

#define BASIC_COLOR 0xb1
#define CHOOSEN_COLOR 0x97

struct INPUTBOX {
    int x, y;
    int owned;
    enum StringType type;
    int length;
    char * target;
};

typedef struct INPUTBOX * inputBox;

inputBox createInputBox(int x, int y, enum StringType type, char * target, int length);
int input(inputBox box);
void clearInputBox(inputBox box); // TODO
void destroyInputBox(inputBox box);

struct CHOICEBOX {
    int x, y;
    unsigned short normalColor;
    unsigned short choosenColor;
    bool choosen;
    char context[100];
    int courseID; // so terrible
    bool alreadySelected;
    bool focusOn;
    bool exist;
};
typedef struct CHOICEBOX *choiceBox;

choiceBox createChoiceBox(int x, int y, unsigned short normalColor, unsigned short choosenColor, const char *text);
void setAlreadySelected(choiceBox cb);
void showChoiceBox(choiceBox cb);
void changeStatus(choiceBox cb);
void setSelect(choiceBox cb);
void clearSelect(choiceBox cb);
void destroyChoiceBox(choiceBox cb);
void focusOff(choiceBox cb[], int n);
void focusOn(choiceBox cb[], int n);

void drawRect(int x, int y, int w, int h, bool fill);
void message(const char * context);
void errorMsg(const char * context);
void msgLine(int x, int y, const char * text);
void msgBox(int x, int y, int w, int h, const char *text);

// 以下三个函数配套使用
void clearRectMap(void);  // 清除缓存的矩形（开始画矩形之前执行一次这个函数）
void setArect(int x, int y, int w, int h);  // 向矩形缓存中增加一个矩形
void drawMultipleRect(void);  // 把缓存写到屏幕上

#endif // GRAPH_H_INCLUDED
