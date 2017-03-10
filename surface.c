#include "console.h"
#include "graph.h"
#include "kbio.h"
#include "courseList.h"
#include "studentsInformation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define DEBUG gotoxy(0,0);printf("focus=%2d firstPos=%2d lastName=%-10s", focus, firstDisplayCoursePosition, displayList->name);

#define MAX_COURSES_IN_PAGE 20

studentinformation login(studentinformation stul)
{
    studentinformation cursor = stul;
    const int x = 34, y = 10;
    int cmd = 0;
    bool quit = false;
    char id[20] = {0}, psd[20] = {0};
    int nID, nPSD;
    clearScreen();

    //setColor(0xff);
    //drawRect(x+2, y-1, 20, 5, true);
    setColor(0xad);
    drawRect(x, y, 20, 5, true);
    msgLine(x+2, y + 1, "ѧ�ţ�");
    msgLine(x+2, y + 3, "���룺");
    inputBox iBox[2];
    iBox[0] = createInputBox(x+8, y+1, number, id, 8); // ѧ�ſ�
    iBox[1] = createInputBox(x+8, y+3, password, psd, 15); // �����

    int focus = 0;
    while(!quit) {
        cmd = input(iBox[focus]);
        clearMsg(0x0f);
        if ((cmd & 0xff00) && (cmd & 0x00ff) == 80 || cmd == 9) {
            // �¼�ͷ��tab
            if (focus < 1)
                focus++;
        }
        else if ((cmd & 0xff00) && (cmd & 0x00ff) == 72) {
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
                //printf("\n%s\n%s\n", id, psd);
                nID = atoi(id);
                //nPSD = atoi(psd);
                while (cursor != NULL) {
                    if (cursor -> id == nID) {
                        if (strcmp(cursor -> password, psd) == 0) {
                            quit = true;
                            break;
                        } else {
                            errorMsg("ѧ�Ż��������");
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
                    errorMsg("ѧ���������");
                }
            }
        }
    }
    destroyInputBox(iBox[0]);
    destroyInputBox(iBox[1]);

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

int menu(studentinformation s)
{
    const int x = 21, y = 8;
    int focus = 0;
    int cmd;
    clearScreen();
    setColor(BASIC_COLOR);
    clearRectMap();
    setArect(x, y, 15, 13);

    drawMultipleRect();
    choiceBox choiceList[5];
    choiceList[0] = createChoiceBox(2*x+4, y+2, BASIC_COLOR, CHOOSEN_COLOR, "     �γ��б�       ");
    choiceList[1] = createChoiceBox(2*x+4, y+4, BASIC_COLOR, CHOOSEN_COLOR, "     ������Ϣ       ");
    choiceList[2] = createChoiceBox(2*x+4, y+6, BASIC_COLOR, CHOOSEN_COLOR, "     �޸�����       ");
    if (s -> id != 0)
        choiceList[3] = createChoiceBox(2*x+4, y+8, BASIC_COLOR, CHOOSEN_COLOR, "     �鿴�α�       ");
    else
        choiceList[3] = createChoiceBox(2*x+4, y+8, BASIC_COLOR, CHOOSEN_COLOR, "     �޸�����       ");
    choiceList[4] = createChoiceBox(2*x+4, y+10, BASIC_COLOR, CHOOSEN_COLOR, "     �˳�ϵͳ       ");
    setSelect(choiceList[focus]);
    while(1) {
        for(int i = 0; i < 5; i++) {
            showChoiceBox(choiceList[i]);
        }
        cmd = getKeyboard();
        if ((cmd & 0xff00) && (cmd & 0x00ff) == 80) {
            if (focus != 4) {
                clearSelect(choiceList[focus]);
                focus++;
                setSelect(choiceList[focus]);
            }
        }
        if ((cmd & 0xff00) && (cmd & 0x00ff) == 72) {
            if (focus != 0) {
                clearSelect(choiceList[focus]);
                focus--;
                setSelect(choiceList[focus]);
            }
        } if (cmd == 13)
            return focus;

    }
    return -1;
}

int addAcourseBox(choiceBox cboxList, courseList *clist)
{
    if (clist == NULL) {
        errorMsg("û�и���γ�");
        return 0;
    }
    char tempString[100];
    sprintf(tempString, "%-30s%-20s%2d           %-3d", clist -> name, clist -> teacherName, clist -> credit, clist -> hours);
    cboxList -> courseID = clist -> id;
    cboxList -> x = 20;
    cboxList -> y = 0;
    cboxList -> normalColor = BASIC_COLOR;
    cboxList -> choosenColor = CHOOSEN_COLOR;
    strcpy(cboxList -> context , tempString);
    cboxList -> choosen = false;
    cboxList -> exist = true;
    return 1;
}

void setCourseListPositon(choiceBox cbl[MAX_COURSES_IN_PAGE], int first)
{
    for (int i = 0; i< MAX_COURSES_IN_PAGE; i++) {
        if (cbl[i] -> exist == false)
            continue;
        cbl[(first + i) % MAX_COURSES_IN_PAGE] -> y = 6 + i;
    }
}

courseList* createCourseBoxListByList(choiceBox cboxList[MAX_COURSES_IN_PAGE], courseList *clist)
{
    for (int i = 0; i < MAX_COURSES_IN_PAGE ; i++) {
        if(clist != NULL) {
            addAcourseBox(cboxList[i], clist);
            clist = clist -> next;
        }
        else
            cboxList[i] -> exist = false;
    }
    return clist;
}

void printSyllabus(courseList *cor, studentinformation stu)
{
    char tstring[20] = {0};
    courseList *tclist = NULL;
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
    msgLine(12, 2, "����һ");
    msgLine(28, 2, "���ڶ�");
    msgLine(44, 2, "������");
    msgLine(60, 2, "������");
    msgLine(76, 2, "������");
    msgLine(92, 2, "������");
    msgLine(108, 2, "������");
    msgBox(2, 6, 4, 4, "һ���ڿ�");
    msgBox(2, 11, 4, 4, "���Ľڿ�");
    msgBox(2, 16, 4, 4, "�����ڿ�");
    msgBox(2, 21, 4, 4, "�߰˽ڿ�");
    msgBox(2, 26, 4, 4, "��ʮ�ڿ�");
    // ÿ�����ӿ�14����4 ��ʼ[8,5]����ÿ��+16������+5 ������a����b�ڣ�
    // x = (a - 1) * 16 + 8 = 16 * a - 8
    // y = (b - 1) * 5 + 5 = 5 * b
    for (int i = 0; i < stu -> endOfCourseArray; i++) {
        if (stu -> endOfCourseArray == 0)
            continue;
        tclist = searchCourseByID(cor, stu->courseid[i]);
        itoa(tclist->time, tstring, 10);
        int l = strlen(tstring);
        for (int j = 0; j < l; j += 2) {
            msgBox(16 * (tstring[j] - '0') - 8 , 5 * (tstring[j+1] - '0'), 14, 4, tclist ->name);
        }
    }
    //msgBox(40, 10, 4, 4, "һ�����������߰˾�ʮ");
    getch();
}


int countElements(courseList *clist)
{
    int a = 0;
    while (clist != NULL) {
        a++;
        clist = clist -> next;
    }
    return a;
}

void clear()
{
    setColor(BASIC_COLOR);
    for (int i = 0 ; i < 20; i++) {
        gotoxy(20, 6 + i);
        printf("%*s", 90, "");
    }
}
int election(courseList * clist, studentinformation cstudent)
{
    bool quit = false;
    clearScreen();
    drawFrame();
    gotoxy(2, 1);
    printf("������%-8s%20sѧԺ��%-56s��ѡ����ѧ�֣�%02d/20", cstudent->name, "", "�������ѧ�빤��ѧԺ", cstudent->credit);
    gotoxy(2, 3);
    printf("�γ̷���:");
    gotoxy(100, 3);
    printf("������");
    setTempColor(0x7f);
    printf("%*s", 10, "");
    resumeColor();

    char tempName[100];
    //inputBox searchBox;
    //searchBox = createInputBox(106, 3, chinese, searchName, 20);

    gotoxy(20, 5);
    printf("%3s�γ�%25s��ʦ%16sѧ��%8sѧʱ", "", "", "" ,"");
    courseList *displayList;
    courseList *searchVer1 = NULL, *searchVer2 = NULL, *selectable;
    choiceBox courseType[3] = {0};
    choiceBox courses[MAX_COURSES_IN_PAGE] = { 0 };
    for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
        courses[i] = createChoiceBox(0, 0, 0, 0, "");
    }
    int focus = 0, cmd = 0;
    int courseTypeListFocus = 0, courseListFocus = 0;
    int firstDisplayCoursePosition = 0; // ��һ��Ҫ��ʾ�Ŀγ��������е�λ��
    int numberOfelements = MAX_COURSES_IN_PAGE;
    bool courseTypeList = true;
    bool nomore = false; // ����û�и���Ԫ��
    courseType[0] = createChoiceBox(2, 4, BASIC_COLOR, CHOOSEN_COLOR, "����ѡ��");
    courseType[1] = createChoiceBox(2, 5, BASIC_COLOR, CHOOSEN_COLOR, "����ѡ��");
    courseType[2] = createChoiceBox(2, 6, BASIC_COLOR, CHOOSEN_COLOR, "רҵѡ��");
    selectable = majorsearch(cstudent -> major, cstudent -> year, -1, clist); // selectable �����������ѧ������רҵ���꼶�Ŀγ�
    displayList = selectable;
    createCourseBoxListByList(courses, displayList);//?
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
            clearMsg0(BASIC_COLOR);
            if ((cmd & 0xff00) && (cmd & 0x00ff) == 80) {
                if (focus == 2)
                    continue;
                else {
                    clearSelect(courseType[focus++]);
                    setSelect(courseType[focus]);
                }
            } else if ((cmd & 0xff00) && (cmd & 0x00ff) == 72) {
                if (focus == 0)
                    continue;
                else {
                    clearSelect(courseType[focus--]);
                    setSelect(courseType[focus]);
                }
            } else if ((cmd & 0xff00) && (cmd & 0x00ff) == 77) {
                courseTypeList = false;
                courseTypeListFocus = focus;
                focus = courseListFocus;
                focusOff(courseType, 3);
                focusOn(courses, MAX_COURSES_IN_PAGE);
            } else if (cmd == 13) {
                // ˢ�¿γ��б� TODO
                destroyCourseList(searchVer1);
                searchVer1 = majorsearch(-1, -1, focus, selectable);
                numberOfelements = countElements(searchVer1);
                displayList = searchVer1;
                for (int i = 0; i < MAX_COURSES_IN_PAGE; i++)
                    courses[i] -> exist = false;
                displayList  = createCourseBoxListByList(courses, displayList);
                courseTypeList = false;
                courseTypeListFocus = focus;
                focus = 0;
                firstDisplayCoursePosition = 0;
                focusOff(courseType, 3);
                focusOn(courses, MAX_COURSES_IN_PAGE);
                clear();
            } else if (cmd == 'q')
                return -1;
        } else {
            setCourseListPositon(courses, firstDisplayCoursePosition);
            setSelect(courses[focus]);
            //clear();
            for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
                showChoiceBox(courses[(firstDisplayCoursePosition + i) % MAX_COURSES_IN_PAGE]);
            }
            //DEBUG

            cmd = getKeyboard();
            clearMsg0(BASIC_COLOR);
            if ((cmd & 0xff00) && (cmd & 0x00ff) == 80) {
                if ( numberOfelements < MAX_COURSES_IN_PAGE || (focus + 1) % MAX_COURSES_IN_PAGE != firstDisplayCoursePosition) {
                    if (numberOfelements < MAX_COURSES_IN_PAGE && focus +1 >= numberOfelements)
                        continue;
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
                        //message("������");
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
            } if ((cmd & 0xff00) && (cmd & 0x00ff) == 72) {
                if (focus != firstDisplayCoursePosition) {
                    // û����
                    //moveDownCourseList(courses);
                    //message("      ");
                    clearSelect(courses[focus--]);
                    if (focus < 0)
                        focus = MAX_COURSES_IN_PAGE -1;
                    //gotoxy(0, 0);
                    //printf("%d", focus);
                    setSelect(courses[focus]);
                } else {

                    //message("������");
                    int t = firstDisplayCoursePosition - 1;
                    t = t < 0 ? MAX_COURSES_IN_PAGE - 1 : t;
                    // TODO
                    if(addAcourseBox(courses[t], lastcourse(courses[firstDisplayCoursePosition] -> courseID, searchVer1))) {
                        if (!nomore)
                            displayList = lastcourse(displayList -> id, searchVer1);

                        firstDisplayCoursePosition = t;
                        clearSelect(courses[focus]);
                        focus = t;
                        setSelect(courses[focus]);
                        setCourseListPositon(courses, firstDisplayCoursePosition);
                    }
                    nomore = false;
                }
            } else if ((cmd & 0xff00) && (cmd & 0x00ff) == 75) {
                courseTypeList = true;
                courseListFocus = focus;
                focus = courseTypeListFocus;
                focusOff(courses, MAX_COURSES_IN_PAGE);
                for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
                    showChoiceBox(courses[(firstDisplayCoursePosition + i) % MAX_COURSES_IN_PAGE]);
                }
            } else if (cmd == 13) {
                //  ���»س�����Ϊ
                if (courses[focus] -> exist)
                    return courses[focus] -> courseID;
            } else if (cmd == 'q')
                return -1;
            else if (cmd == 's') {
                inputDialog("������γ�����", tempName);
                destroyCourseList(searchVer2);
                searchVer2 = namesearch(tempName, clist);
                destroyCourseList(searchVer1);
                searchVer1 = searchVer2;
                displayList = searchVer1;
                for (int i = 0; i < MAX_COURSES_IN_PAGE; i++)
                    courses[i] -> exist = false;
                displayList  = createCourseBoxListByList(courses, displayList);
                focus = 0;
                firstDisplayCoursePosition = 0;
                clear();
            }
        }
    }
    destroyChoiceBox(courseType[0]);
    destroyChoiceBox(courseType[1]);
    destroyChoiceBox(courseType[2]);
    for (int i = 0; i < MAX_COURSES_IN_PAGE; i++) {
        destroyChoiceBox(courses[i]);
    }
    free(selectable);
    return -1;
}

char *itoA(int a)
{
    return itoa(a, TEMP_STRING, 10);
}

void showStudentInformation(courseList *cour, studentinformation stu)
{
    gotoxy(0, 0);
    clearRectMap();
    setArect(10, 7, 39, 14);
    setArect(11, 8, 10, 12);
    drawMultipleRect();
    msgLine(52, 10, "������");
    msgLine(58, 10, stu->name);
    msgLine(76, 10, "ѧ�ţ�");
    msgLine(82, 10, itoA(stu->id));
    msgLine(52, 13, "�꼶��");
    msgLine(58, 13, itoA(stu-> year));
    msgLine(76, 13, "רҵ��");
    msgLine(82, 13, itoA((int)stu->major));
}


void changePsd(studentinformation stu)
{
    char oldPsd[20], newPsd[20], rePsd[20];
    clearScreen();
    int x = 16, y = 8;
    inputBox list[3];
    list[0] = createInputBox(2 * x + 14, y + 2, password, oldPsd, 15);
    list[1] = createInputBox(2 * x + 14, y + 5, password, newPsd, 15);
    list[2] = createInputBox(2 * x + 14, y + 8, password, rePsd, 15);
    int focus = 0;
    clearRectMap();
    setArect(x, y, 25, 13);
    setArect(x + 6, y + 1, 18, 3);
    setArect(x + 6, y + 4, 18, 3);
    setArect(x + 6, y + 7, 18, 3);
    drawMultipleRect();
    msgLine(2 * x + 3, y + 2, "  ������");
    msgLine(2 * x + 3, y + 5, "  ������");
    msgLine(2 * x + 3, y + 8, "�ظ�����");
    bool quit = false;
    int cmd;
    while(!quit)
    {
        cmd = input(list[focus]);
        switch(cmd & 0x00ff)
        {
        case 80:
        case 9:
            if (focus < 2) {
                focus += 1;
            }
            break;
        case 72:
            if (focus > 0) {
                focus -= 1;
            }
            break;
        case 13:
            if (strcmp(stu -> password, oldPsd) == 0) {
                if (strcmp(newPsd, rePsd) == 0) {
                    strcpy(stu -> password, newPsd);
                    dialog("�����޸ĳɹ�");
                    quit = true;
                } else {
                    errorMsg("�������벻һ��");
                }
            } else  {
                errorMsg("�������������");
            }
            break;
        }
    }
}

