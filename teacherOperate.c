#include "teacherOperate.h"
#include "studentsInformation.h"
#include "courseList.h"
#include "graph.h"
#include "console.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define moveOn(x,y) if(syllabus[y][x]){setRectF(x,y);}else{setRectB(x,y);}
#define moveOut(x,y) if(syllabus[y][x]){setChecked(x,y);}else{setDot(x,y);}
int t_menu()
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
    choiceList[0] = createChoiceBox(2*x+4, y+2, BASIC_COLOR, CHOOSEN_COLOR, "     ���ѧ��       ");
    choiceList[1] = createChoiceBox(2*x+4, y+4, BASIC_COLOR, CHOOSEN_COLOR, "     ɾ��ѧ��       ");
    choiceList[2] = createChoiceBox(2*x+4, y+6, BASIC_COLOR, CHOOSEN_COLOR, "     ��ӿγ�       ");
    choiceList[3] = createChoiceBox(2*x+4, y+8, BASIC_COLOR, CHOOSEN_COLOR, "     ɾ���γ�       ");
    choiceList[4] = createChoiceBox(2*x+4, y+10, BASIC_COLOR, CHOOSEN_COLOR, "     ���ݻָ�       ");
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
        else if ((cmd & 0xff00) && (cmd & 0x00ff) == 72) {
            if (focus != 0) {
                clearSelect(choiceList[focus]);
                focus--;
                setSelect(choiceList[focus]);
            }
        } else if (cmd == 13) {
            return focus;

        } else if (cmd == 'q')
            return -1;
    }
    return -1;
}

studentinformation addStudent(void)
{
    studentinformation ret = (studentinformation)malloc(sizeof(struct student));
    memset(ret, 0, sizeof(struct student));
    inputDialog("������ѧ������", ret -> name);
    char id[20], major[20], grade[20], clas[20];
    clearScreen();
    int x = 16, y = 6;
    inputBox list[4];
    list[0] = createInputBox(2 * x + 14, y + 5, number, id, 15);
    list[1] = createInputBox(2 * x + 14, y + 8, number, major, 15);
    list[2] = createInputBox(2 * x + 14, y + 11, number, grade, 15);
    list[3] = createInputBox(2 * x + 14, y + 14, number, clas, 15);
    int focus = 0;
    clearRectMap();
    setArect(x, y, 25, 19);
    setArect(x + 6, y + 4, 18, 3);
    setArect(x + 6, y + 7, 18, 3);
    setArect(x + 6, y + 10, 18, 3);
    setArect(x + 6, y + 13, 18, 3);
    drawMultipleRect();
    msgLine(2 * x + 3, y + 2, "    ����");
    msgLine(2 * x + 14, y + 2, ret -> name);
    msgLine(2 * x + 3, y + 5, "    ѧ��");
    msgLine(2 * x + 3, y + 8, "רҵ����");
    msgLine(2 * x + 3, y + 11, "    �꼶");
    msgLine(2 * x + 3, y + 14, "    �༶");
    bool quit = false;
    int cmd;
    while(!quit)
    {
        cmd = input(list[focus]);
        clearMsg(BASIC_COLOR);
        switch(cmd & 0x00ff)
        {
        case 80:
        case 9:
            if (focus < 3) {
                focus += 1;
            }
            break;
        case 72:
            if (focus > 0) {
                focus -= 1;
            }
            break;
        case 13:
            if (!(strlen(id) && strlen(major) && strlen(grade) && strlen(clas))) {
                errorMsg("��δ��д����Ŀ");
                continue;
            }
            ret -> id = atoi(id);
            ret -> major = atoi(major);
            ret -> classes = atoi(clas);
            ret -> year = atoi(grade);
            strcpy(ret -> password, id);
            quit = true;
        }
    }
    return ret;
}

void setChecked(int x, int y)
{
    gotoxy(4 * x + 52 , 2 * y + 5);
    setColor(BASIC_COLOR);
    printf("��");
}
void setDot(int x, int y)
{
    gotoxy(4 * x + 52 , 2 * y + 5);
    setColor(BASIC_COLOR);
    printf("��");
}

void setRectB(int x, int y)
{
    gotoxy(4 * x + 52 , 2 * y + 5);
    setColor(BASIC_COLOR);
    printf("��");
}

void setRectF(int x, int y)
{
    gotoxy(4 * x + 52 , 2 * y + 5);
    setColor(BASIC_COLOR);
    printf("��");
}

courseList *_addCourse(void)
{
    const int x = 0, y = 0;
    const int syllabusX = x + 25, syllabusY = y + 4;
    courseList *ret = (courseList*)malloc(sizeof(struct COURSE));
    memset(ret, 0, sizeof(struct COURSE));
    //strcpy(ret -> name, "ʱ���ڳ�ѧ");
    //strcpy(ret -> teacherName, "��");
    inputDialog("������γ�����", ret -> name);
    inputDialog("�������ʦ����", ret -> teacherName);
    char id[20], credit[20], hours[20], maxStu[20], grade[20];
    clearScreen();

    inputBox list[5];
    list[0] = createInputBox(2 * x + 14, y + 8, number, id, 15);
    list[1] = createInputBox(2 * x + 14, y + 11, number, credit, 15);
    list[2] = createInputBox(2 * x + 14, y + 14, number, hours, 15);
    list[3] = createInputBox(2 * x + 14, y + 17, number, maxStu, 15);
    list[4] = createInputBox(2 * x + 14, y + 20, number, grade, 15);
    //list[5] = createInputBox(2 * x + 14, y + 23, number, major, 15);
    choiceBox type[3];
    type[0] = createChoiceBox(2 * syllabusX + 2, 18, BASIC_COLOR, CHOOSEN_COLOR, "   ����ѡ��  ");
    type[1] = createChoiceBox(2 * syllabusX + 2, 20, BASIC_COLOR, CHOOSEN_COLOR, "   ����ѡ��  ");
    type[2] = createChoiceBox(2 * syllabusX + 2, 22, BASIC_COLOR, CHOOSEN_COLOR, "   רҵѡ��  ");
    focusOff(type, 3);
    setColor(BASIC_COLOR);

    choiceBox major[8];
    major[0] = createChoiceBox(100, 4, BASIC_COLOR, CHOOSEN_COLOR, "�����");
    major[1] = createChoiceBox(100, 6, BASIC_COLOR, CHOOSEN_COLOR, " ���� ");
    major[2] = createChoiceBox(100, 8, BASIC_COLOR, CHOOSEN_COLOR, " ���� ");
    major[3] = createChoiceBox(100, 10, BASIC_COLOR, CHOOSEN_COLOR, " �ķ� ");
    major[4] = createChoiceBox(100, 12, BASIC_COLOR, CHOOSEN_COLOR, " ��е ");
    major[5] = createChoiceBox(100, 14, BASIC_COLOR, CHOOSEN_COLOR, " ��ѧ ");
    major[6] = createChoiceBox(100, 16, BASIC_COLOR, CHOOSEN_COLOR, " Ӣ�� ");
    major[7] = createChoiceBox(100, 18, BASIC_COLOR, CHOOSEN_COLOR, " ұ�� ");
    focusOff(major, 8);
    setColor(BASIC_COLOR);


    clearRectMap();
    //�����
    setArect(x, y, 60, 29);
    setArect(x + 6, y + 1, 14, 3);
    setArect(x + 6, y + 4, 14, 3);
    setArect(x + 6, y + 7, 14, 3);
    setArect(x + 6, y + 10, 14, 3);
    setArect(x + 6, y + 13, 14, 3);
    setArect(x + 6, y + 16, 14, 3);
    setArect(x + 6, y + 19, 14, 3);
    //�γ̱����
    setArect(syllabusX, syllabusY, 15, 11);
    setArect(syllabusX, syllabusY + 2, 15, 3);
    setArect(syllabusX, syllabusY + 6, 15, 3);
    setArect(syllabusX + 2, syllabusY, 3, 11);
    setArect(syllabusX + 6, syllabusY, 3, 11);
    setArect(syllabusX + 10, syllabusY, 3, 11);
    // �����б�
    setArect(syllabusX, 17, 10, 7);
    setArect(syllabusX, 19, 10, 3);
    // רҵ�б�
    setArect(49, 3, 6, 17);
    setArect(49, 5, 6, 3);
    setArect(49, 9, 6, 3);
    setArect(49, 13, 6, 3);
    setArect(49, 17, 6, 3);
    drawMultipleRect();
    msgLine(2 * x + 3, y + 2, "    ����");
    msgLine(2 * x + 14, y + 2, ret -> name);
    msgLine(2 * x + 3, y + 5, "��ʦ����");
    msgLine(2 * x + 14, y + 5, ret -> teacherName);
    msgLine(2 * x + 3, y + 8, "�γ̱��");
    msgLine(2 * x + 3, y + 11, "    ѧ��");
    msgLine(2 * x + 3, y + 14, "    ѧʱ");
    msgLine(2 * x + 3, y + 17, "ѧ������");
    msgLine(2 * x + 3, y + 20, "    �꼶");

    bool syllabus[5][7];
    memset(syllabus, 0, sizeof(syllabus));

    msgLine(syllabusX* 2 + 2, syllabusY - 1, "һ  ��  ��  ��  ��  ��  ��");
    for (int y1 = y; y1 < 5 ; y1 ++) {
        for (int x1 = x; x1 < 7; x1++) {
            setDot(x1, y1);
        }
    }
    bool inSyllabus = false;
    bool inInputList = true;
    bool inmajorList = false;
    bool inTypeList = false;
    bool quit = false;
    int week = 0, time = 0;
    int focus = 0;
    int typeFocus = 0, majorFocus = 0;
    int cmd;
    clearMsg(BASIC_COLOR);

    setSelect(type[typeFocus]);
    setSelect(major[majorFocus]);

    while(!quit)
    {
        for(int i = 0; i < 3; i++)
            showChoiceBox(type[i]);
        for(int i = 0; i < 8; i++)
            showChoiceBox(major[i]);
        if (inInputList) {
            setColor(BASIC_COLOR);
            cmd = input(list[focus]);
        }
        else
            cmd = getKeyboard();
        clearMsg(BASIC_COLOR);
        switch(cmd & 0x00ff)
        {
        case 80:
            // ����
            if (inInputList) {
                if (focus < 4) {
                    focus += 1;
                }
            } else if (inSyllabus) {
                if (time < 4) {
                    moveOut(week, time);
                        // ���ԭ����û�б�ѡ
                    time += 1;
                    moveOn(week, time);
                } else {
                    inSyllabus = false;
                    inTypeList = true;
                    focusOn(type, 3);
                    setSelect(type[typeFocus]);
                }
            } else if(inTypeList) {
                if (typeFocus < 2) {
                    clearSelect(type[typeFocus]);
                    typeFocus += 1;
                    setSelect(type[typeFocus]);
                }
            } else if(inmajorList) {
                if (majorFocus < 7) {
                    clearSelect(major[majorFocus]);
                    majorFocus += 1;
                    setSelect(major[majorFocus]);
                }
            }
            break;
        case 72:
            // ����
            if (inInputList) {
                if (focus > 0) {
                    focus -= 1;
                }
            } else if (inSyllabus) {
                if (time > 0) {
                    moveOut(week, time);
                    time -= 1;
                    moveOn(week, time);
                }
            } else if (inTypeList) {
                if (typeFocus > 0) {
                    clearSelect(type[typeFocus]);
                    typeFocus -= 1;
                    setSelect(type[typeFocus]);
                } else {
                    inTypeList = false;
                    inSyllabus = true;
                    focusOff(type, 3);
                    setColor(BASIC_COLOR);
                }
            } else if(inmajorList) {
                if (majorFocus > 0) {
                    clearSelect(major[majorFocus]);
                    majorFocus -= 1;
                    setSelect(major[majorFocus]);
                }
            }
            break;
        case 75:
            // ����
            if (inInputList)
                ;
            else if (inSyllabus){
                if (week > 0) {
                    moveOut(week, time);
                    week -= 1;
                    moveOn(week, time);
                } else {
                    moveOut(week, time);
                    inSyllabus = false;
                    inInputList = true;
                }
            } else if (inTypeList) {
                focusOff(type, 3);
                setColor(BASIC_COLOR);
                inTypeList = false;
                inInputList = true;
            } else if(inmajorList) {
                inmajorList = false;
                if (majorFocus > 5) {
                    focusOn(type, 3);
                    inTypeList = true;
                } else {
                    inSyllabus = true;
                }
            }
            break;
        case 77:
            // ����
            if (inInputList) {
                inInputList = false;
                inSyllabus = true;
                moveOn(week, time);

            } else if (inSyllabus) {
                if (week < 6) {
                    moveOut(week, time);
                    week += 1;
                    moveOn(week, time);
                } else {
                    moveOut(week, time);
                    inSyllabus = false;
                    inmajorList = true;
                    focusOn(major, 8);
                }
            } else if (inTypeList) {
                focusOff(type, 3);
                setColor(BASIC_COLOR);
                inTypeList = false;
                inmajorList = true;
                focusOn(major, 8);
            } else if (inmajorList)
                ;
            break;
        case 32:
            // �ո�
            if (inSyllabus) {
                syllabus[time][week] = !syllabus[time][week];
                moveOn(week, time);
            } else if(inmajorList) {
                major[majorFocus] -> alreadySelected = !major[majorFocus] -> alreadySelected;
            }
            break;
        case 13:
            // �س�
            if (!(strlen(id)  && strlen(credit) && strlen(hours)
                  && strlen(maxStu) && strlen(grade))) {
                errorMsg("��δ��д����Ŀ");
                continue;
            }
            ret -> id = atoi(id);
            ret -> credit = atoi(credit);
            ret -> hours = atoi(hours);
            ret -> maxStudent = atoi(maxStu);
            ret -> grade = atoi(grade);
            ret -> type = typeFocus;

            for (int w = 0; w < 7; w++) {
                for (int t = 0; t < 5; t++) {
                    if (syllabus[t][w]) {
                        ret -> time = (ret -> time) * 100 + (w + 1) * 10 + ( t + 1);
                    }
                }
            }

            for (int i = 0; i < 8; i++) {
                if (major[i] -> alreadySelected)
                    ret -> major |=  (0x01 << i);
            }
            quit = true;
        }
    }
    return ret;
}
void teacherOperate(courseList *cl, studentinformation stu)
{
    bool quit = false;
    char temp[200];
    int cmd;
    courseList *ta;
    FILE * stu_f = fopen("students.bak", "r");
    FILE * cor_f = fopen("course.bak", "r");
    while(!quit)
    {
        cmd = t_menu();
        switch(cmd)
        {
        case -1:
            return;
            break;
        case 0:
            insertstudent(stu, addStudent());
            break;
        case 1:
            inputDialog("����ѧ�����", temp);
            deletestudent(stu, atoi(temp));
            break;
        case 2:
            ta = _addCourse();
            addCourse(ta, cl);
            free(ta);
            break;
        case 3:
            inputDialog("����γ̱��", temp);
            ta = searchCourseByID(cl, atoi(temp));
            removeCourse(ta, cl);
            break;
        case 4:


            if (stu_f != NULL && cor_f != NULL) {
                if (confirm("��⵽�����ļ����Ƿ�ָ�")) {
                    system("resume.bat");
                    message("�ָ��ɹ�");
                    break;
                }
            }

            fflush(stdin);

            if (confirm("�Ƿ���б���")) {
                    system("bk.bat");
                    message("���ݳɹ�");
                    fclose(stu_f);
                    fclose(cor_f);
                    stu_f = fopen("students.bak", "r");
                    cor_f = fopen("course.bak", "r");
            }

            break;
        }
    }
    fclose(stu_f);
    fclose(cor_f);
}
