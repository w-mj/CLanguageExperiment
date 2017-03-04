#include "console.h"
#include "graph.h"
#include "kbio.h"
#include "courseList.h"
#include <stdio.h>
#include <string.h>

#define DEBUG gotoxy(0,0);printf("focus=%2d firstPos=%2d lastName=%-10s", focus, firstDisplayCoursePosition, displayList->name);

#define MAX_COURSES_IN_PAGE 20

void login(void)
{
    const int x = 33, y = 10;
    int cmd = 0;
    bool quit = false;
    char id[20] = {0}, psd[20] = {0};
    clearScreen();
    showCursor();
    setColor(0xad);
    drawRect(x, y, 20, 5, true);
    msgBox(x+2, y + 1, 6, 1, "ѧ�ţ�");
    msgBox(x+2, y + 3, 6, 1, "���룺");
    inputBox iBox[2];
    iBox[0] = createInputBox(x+8, y+1, number, id, 8); // ѧ�ſ�
    iBox[1] = createInputBox(x+8, y+3, password, psd, 15); // �����

    int focus = 0;
    while(!quit) {
        cmd = input(iBox[focus]);
        if (cmd == -80 || cmd == 9) {
            // �¼�ͷ��tab
            if (focus < 1)
                focus++;
        }
        else if (cmd == -72) {
            // �ϼ�ͷ
            if (focus > 0)
            focus--;
        }else if (cmd == 13) {
            // �س�
            if (strlen(id) == 0) {
                errorMsg("ѧ�Ų���Ϊ�գ�");
            } else if (strlen(psd) == 0) {
                errorMsg("���벻��Ϊ�գ�");
            } else {
                // TODO
                //printf("\n%s\n%s\n", id, psd);
                quit = true;
            }
        }
    }
    destroyInputBox(iBox[0]);
    destroyInputBox(iBox[1]);
    hideCursor();
    return;
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

int addAcourseBox(choiceBox cboxList, courseList *clist)
{
    if (clist == NULL) {
        errorMsg("û�и���γ�");
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


void election(courseList * clist)
{
    bool quit = false;
    gotoxy(2, 1);
    printf("������%-8s%20sѧԺ��%-56s��ѡ����ѧ�֣�%02d/20", "��С��", "", "�������ѧ�빤��ѧԺ", 18);
    gotoxy(2, 3);
    printf("�γ̷���:");
    gotoxy(100, 3);
    printf("������");
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
    int firstDisplayCoursePosition = 0; // ��һ��Ҫ��ʾ�Ŀγ��������е�λ��
    bool courseTypeList = true;
    bool nomore = false; // ����û�и���Ԫ��
    courseType[0] = createChoiceBox(2, 4, BASIC_COLOR, CHOOSEN_COLOR, "����ѡ��");
    courseType[1] = createChoiceBox(2, 5, BASIC_COLOR, CHOOSEN_COLOR, "����ѡ��");
    courseType[2] = createChoiceBox(2, 6, BASIC_COLOR, CHOOSEN_COLOR, "רҵѡ��");
    while (!quit) {
        if (courseTypeList) {
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
            } else if (cmd == 13) {
                // ˢ�¿γ��б� TODO
                displayList  = createCourseBoxListByList(courses, displayList);
                courseTypeList = false;
                courseTypeListFocus = focus;
                focus = courseListFocus;
            }
        } else {
            setCourseListPositon(courses, firstDisplayCoursePosition);
            setSelect(courses[focus]);
            DEBUG
            for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
                showChoiceBox(courses[(firstDisplayCoursePosition + i) % MAX_COURSES_IN_PAGE]);
            }
            cmd = getKeyboard();
            if (cmd == -80) {
                if ((focus + 1) % MAX_COURSES_IN_PAGE != firstDisplayCoursePosition) {
                    message("      ");
                    // û����
                    clearSelect(courses[focus++]);
                    if (focus == MAX_COURSES_IN_PAGE)
                        focus = 0;
                    setSelect(courses[focus]);
                } else {
                    if((!nomore) && addAcourseBox(courses[firstDisplayCoursePosition], displayList)) {
                            // displayList ʼ��ָ����ʾ�б�����һ��Ԫ��
                        if (displayList -> next != NULL)
                            displayList = displayList -> next;
                        else
                            nomore = true;
                        message("������");
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
                    // û����
                    //moveDownCourseList(courses);
                    message("      ");
                    clearSelect(courses[focus--]);
                    if (focus < 0)
                        focus = MAX_COURSES_IN_PAGE -1;
                    gotoxy(0, 0);
                    printf("%d", focus);
                    setSelect(courses[focus]);
                } else {

                    message("������");
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
            } else if (cmd == 13) {
                // TODO  ���»س�����Ϊ
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
