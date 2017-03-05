#include "console.h"
#include "graph.h"
#include "kbio.h"
#include "courseList.h"
#include "studentsInformation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG gotoxy(0,0);printf("focus=%2d firstPos=%2d lastName=%-10s", focus, firstDisplayCoursePosition, displayList->name);

#define MAX_COURSES_IN_PAGE 20

studentinformation login(studentinformation stul)
{
    studentinformation cursor = stul;
    const int x = 33, y = 10;
    int cmd = 0;
    bool quit = false;
    char id[20] = {0}, psd[20] = {0};
    int nID, nPSD;
    clearScreen();
    showCursor();
    //setColor(0xff);
    //drawRect(x+2, y-1, 20, 5, true);
    setColor(0xad);
    drawRect(x, y, 20, 5, true);
    msgLine(x+2, y + 1, "学号：");
    msgLine(x+2, y + 3, "密码：");
    inputBox iBox[2];
    iBox[0] = createInputBox(x+8, y+1, number, id, 8); // 学号框
    iBox[1] = createInputBox(x+8, y+3, password, psd, 15); // 密码框

    int focus = 0;
    while(!quit) {
        cmd = input(iBox[focus]);
        if (cmd == -80 || cmd == 9) {
            // 下箭头和tab
            if (focus < 1)
                focus++;
        }
        else if (cmd == -72) {
            // 上箭头
            if (focus > 0)
            focus--;
        }else if (cmd == 13) {
            // 回车
            if (strlen(id) == 0) {
                errorMsg("学号不能为空！");
            } else if (strlen(psd) == 0) {
                errorMsg("密码不能为空！");
            } else {
                //printf("\n%s\n%s\n", id, psd);
                nID = atoi(id);
                nPSD = atoi(psd);
                while (cursor != NULL) {
                    if (cursor -> id == nID) {
                        if (cursor -> password == nPSD) {
                            quit = true;
                            break;
                        } else {
                            errorMsg("学号或密码错误");
                            focus = 1;
                            clearInputBox(iBox[focus]);
                            break;
                        }
                    } else {
                        cursor = cursor -> next;
                    }
                }
                if (cursor == NULL) {
                    cursor = stul;
                    focus = 0;
                    clearInputBox(iBox[0]);
                    clearInputBox(iBox[1]);
                    errorMsg("学号输入错误");
                }
            }
        }
    }
    destroyInputBox(iBox[0]);
    destroyInputBox(iBox[1]);
    hideCursor();
    return cursor;
}

void drawFrame(void)
{
    clearRectMap();
    setArect(0, 0, 60, 30);
    setArect(0, 0, 60, 3);
    setArect(0, 2, 8, 26);
    setArect(7, 4, 53, 24);
    drawMultipleRect();
}

int menu(void)
{
    const int x = 21, y = 8;
    int focus = 0;
    char ch;
    clearScreen();
    setColor(BASIC_COLOR);
    clearRectMap();
    setArect(x, y, 15, 13);
    /*
    setArect(x + 1, y + 1, 13, 3);
    setArect(x + 1, y + 4, 13, 3);
    setArect(x + 1, y + 7, 13, 3);
    setArect(x + 1, y + 10, 13, 3);
    setArect(x + 1, y + 13, 13, 3);
    */
    drawMultipleRect();
    choiceBox choiceList[5];
    choiceList[0] = createChoiceBox(2*x+4, y+2, BASIC_COLOR, CHOOSEN_COLOR, "     课程列表       ");
    choiceList[1] = createChoiceBox(2*x+4, y+4, BASIC_COLOR, CHOOSEN_COLOR, "     个人信息       ");
    choiceList[2] = createChoiceBox(2*x+4, y+6, BASIC_COLOR, CHOOSEN_COLOR, "     修改密码       ");
    choiceList[3] = createChoiceBox(2*x+4, y+8, BASIC_COLOR, CHOOSEN_COLOR, "     查看课表       ");
    choiceList[4] = createChoiceBox(2*x+4, y+10, BASIC_COLOR, CHOOSEN_COLOR, "     退出系统       ");
    setSelect(choiceList[focus]);
    while(1) {
        for(int i = 0; i < 5; i++) {
            showChoiceBox(choiceList[i]);
        }
        ch = getKeyboard();
        if (ch == -80) {
            if (focus != 4) {
                clearSelect(choiceList[focus]);
                focus++;
                setSelect(choiceList[focus]);
            }
        }
        if (ch == -72) {
            if (focus != 0) {
                clearSelect(choiceList[focus]);
                focus--;
                setSelect(choiceList[focus]);
            }
        } if (ch == 13)
            return focus;

    }
    return -1;
}

int addAcourseBox(choiceBox cboxList, courseList *clist)
{
    if (clist == NULL) {
        errorMsg("没有更多课程");
        return 0;
    }
    char tempString[100];
    sprintf(tempString, "%20s%20s%d%d%d", clist -> name, clist -> teacherName, clist -> credit, clist -> hours);
    cboxList -> courseID = clist -> id;
    cboxList -> x = 20;
    cboxList -> y = 0;
    cboxList -> normalColor = BASIC_COLOR;
    cboxList -> choosenColor = CHOOSEN_COLOR;
    strcpy(cboxList -> context , tempString);
    cboxList -> choosen = false;
    return 1;
}

void setCourseListPositon(choiceBox cbl[MAX_COURSES_IN_PAGE], int first)
{
    for (int i = 0; i< MAX_COURSES_IN_PAGE; i++) {
        cbl[(first + i) % MAX_COURSES_IN_PAGE] -> y = 7 + i;
    }
}

courseList* createCourseBoxListByList(choiceBox cboxList[MAX_COURSES_IN_PAGE], courseList *clist)
{
    for (int i = 0; i < MAX_COURSES_IN_PAGE ; i++) {
        addAcourseBox(cboxList[i], clist);
        clist = clist -> next;
    }
    return clist;
}

void printSyllabus(void)
{
    clearScreen();
    clearRectMap();
    setArect(0, 0, 60, 30);
    setArect(0, 0, 60, 5);
    setArect(0, 9, 60, 1);
    setArect(0, 14, 60, 1);
    setArect(0, 19, 60, 1);
    setArect(0, 24, 60, 1);
    setArect(3, 0, 1, 30);
    setArect(11, 0, 1, 30);
    setArect(19, 0, 1, 30);
    setArect(27, 0, 1, 30);
    setArect(35, 0, 1, 30);
    setArect(43, 0, 1, 30);
    setArect(51, 0, 1, 30);
    drawMultipleRect();
    msgLine(12, 2, "星期一");
    msgLine(28, 2, "星期二");
    msgLine(44, 2, "星期三");
    msgLine(60, 2, "星期四");
    msgLine(76, 2, "星期五");
    msgLine(92, 2, "星期六");
    msgLine(108, 2, "星期日");
    msgBox(2, 6, 4, 4, "一二节课");
    msgBox(2, 11, 4, 4, "三四节课");
    msgBox(2, 16, 4, 4, "五六节课");
    msgBox(2, 21, 4, 4, "七八节课");
    msgBox(2, 26, 4, 4, "九十节课");
    while(1);
}


void election(courseList * clist, studentinformation cstudent)
{
    bool quit = false;
    clearScreen();
    drawFrame();
    gotoxy(2, 1);
    printf("姓名：%-8s%20s学院：%-56s已选课总学分：%02d/20", cstudent->name, "", "计算机科学与工程学院", cstudent->credit);
    gotoxy(2, 3);
    printf("课程分类:");
    gotoxy(100, 3);
    printf("搜索：");
    setTempColor(0x7f);
    printf("%*s", 10, "");
    resumeColor();

    courseList *subList = clist;
    courseList *displayList = subList;
    choiceBox courseType[3] = {0};
    choiceBox courses[MAX_COURSES_IN_PAGE] = { 0 };
    for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
        courses[i] = createChoiceBox(0, 0, 0, 0, "");
    }
    int focus = 0, cmd = 0;
    int courseTypeListFocus = 0, courseListFocus = 0;
    int firstDisplayCoursePosition = 0; // 第一个要显示的课程在数组中的位置
    bool courseTypeList = true;
    bool nomore = false; // 向下没有更多元素
    courseType[0] = createChoiceBox(2, 4, BASIC_COLOR, CHOOSEN_COLOR, "人文选修");
    courseType[1] = createChoiceBox(2, 5, BASIC_COLOR, CHOOSEN_COLOR, "公共选修");
    courseType[2] = createChoiceBox(2, 6, BASIC_COLOR, CHOOSEN_COLOR, "专业选修");
    createCourseBoxListByList(courses, displayList);
    setCourseListPositon(courses, firstDisplayCoursePosition);
    focusOff(courses, MAX_COURSES_IN_PAGE);
    for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
        showChoiceBox(courses[(firstDisplayCoursePosition + i) % MAX_COURSES_IN_PAGE]);
    }
    while (!quit) {
        showChoiceBox(courseType[0]);
        showChoiceBox(courseType[1]);
        showChoiceBox(courseType[2]);

        if (courseTypeList) {
            focusOn(courseType, 3);
            setSelect(courseType[focus]);
            showChoiceBox(courseType[0]);
            showChoiceBox(courseType[1]);
            showChoiceBox(courseType[2]);
            cmd = getKeyboard();
            if (cmd == -80) {
                if (focus == 2)
                    continue;
                else {
                    clearSelect(courseType[focus++]);
                    setSelect(courseType[focus]);
                }
            } else if (cmd == -72) {
                if (focus == 0)
                    continue;
                else {
                    clearSelect(courseType[focus--]);
                    setSelect(courseType[focus]);
                }
            } else if (cmd == -77) {
                courseTypeList = false;
                courseTypeListFocus = focus;
                focus = courseListFocus;
                focusOff(courseType, 3);
            } else if (cmd == 13) {
                // 刷新课程列表 TODO
                displayList  = createCourseBoxListByList(courses, displayList);
                courseTypeList = false;
                courseTypeListFocus = focus;
                focus = courseListFocus;
                focusOff(courseType, 3);
            }
        } else {
            focusOn(courses, MAX_COURSES_IN_PAGE);
            setCourseListPositon(courses, firstDisplayCoursePosition);
            setSelect(courses[focus]);
            for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
                showChoiceBox(courses[(firstDisplayCoursePosition + i) % MAX_COURSES_IN_PAGE]);
            }
            //DEBUG

            cmd = getKeyboard();
            if (cmd == -80) {
                if ((focus + 1) % MAX_COURSES_IN_PAGE != firstDisplayCoursePosition) {
                    //message("      ");
                    // 没到底
                    clearSelect(courses[focus++]);
                    if (focus == MAX_COURSES_IN_PAGE)
                        focus = 0;
                    setSelect(courses[focus]);
                } else {
                    if((!nomore) && addAcourseBox(courses[firstDisplayCoursePosition], displayList)) {
                            // displayList 始终指向显示列表的最后一个元素
                        if (displayList -> next != NULL)
                            displayList = displayList -> next;
                        else
                            nomore = true;
                        //message("到底了");
                        firstDisplayCoursePosition += 1;
                        firstDisplayCoursePosition %= MAX_COURSES_IN_PAGE;
                        clearSelect(courses[focus]);
                        focus = firstDisplayCoursePosition - 1;
                        if (focus < 0)
                            focus = MAX_COURSES_IN_PAGE - 1;
                        setSelect(courses[focus]);
                        setCourseListPositon(courses, firstDisplayCoursePosition);
                    }
                }
            } if (cmd == -72) {
                if (focus != firstDisplayCoursePosition) {
                    // 没到顶
                    //moveDownCourseList(courses);
                    //message("      ");
                    clearSelect(courses[focus--]);
                    if (focus < 0)
                        focus = MAX_COURSES_IN_PAGE -1;
                    //gotoxy(0, 0);
                    //printf("%d", focus);
                    setSelect(courses[focus]);
                } else {

                    //message("到顶了");
                    int t = firstDisplayCoursePosition - 1;
                    t = t < 0 ? MAX_COURSES_IN_PAGE - 1 : t;
                    // TODO
                    if(addAcourseBox(courses[t], lastcourse(courses[firstDisplayCoursePosition] -> courseID, subList))) {
                        if (!nomore)
                            displayList = lastcourse(displayList -> id, subList);

                        firstDisplayCoursePosition = t;
                        clearSelect(courses[focus]);
                        focus = t;
                        setSelect(courses[focus]);
                        setCourseListPositon(courses, firstDisplayCoursePosition);
                    }
                    nomore = false;
                }
            } else if (cmd == -75) {
                courseTypeList = true;
                courseListFocus = focus;
                focus = courseTypeListFocus;
                focusOff(courses, MAX_COURSES_IN_PAGE);
                for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
                    showChoiceBox(courses[(firstDisplayCoursePosition + i) % MAX_COURSES_IN_PAGE]);
                }
            } else if (cmd == 13) {
                // TODO  按下回车的行为
                return 0;
            }
        }
    }
    destroyChoiceBox(courseType[0]);
    destroyChoiceBox(courseType[1]);
    destroyChoiceBox(courseType[2]);
    for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
        destroyChoiceBox(courses[i]);
    }
}
