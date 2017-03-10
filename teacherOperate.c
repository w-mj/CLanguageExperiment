#include "teacherOperate.h"
#include "studentsInformation.h"
#include "courseList.h"
#include "graph.h"

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
    choiceList[4] = createChoiceBox(2*x+4, y+10, BASIC_COLOR, CHOOSEN_COLOR, "     �����ϼ�       ");
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

studentinformation addStudent(void)
{
    studentinformation ret = (studentinformation)malloc(sizeof(struct student));
    memset(ret, 0, sizeof(struct student));
    inputDialog("������ѧ������", ret -> name);
    char id[20], major[20], grade[20], clas[20];
    clearScreen();
    int x = 16, y = 6;
    inputBox list[4];
    list[0] = createInputBox(2 * x + 14, y + 5, password, id, 15);
    list[1] = createInputBox(2 * x + 14, y + 8, password, major, 15);
    list[2] = createInputBox(2 * x + 14, y + 11, password, grade, 15);
    list[3] = createInputBox(2 * x + 14, y + 14, password, clas, 15);
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
            if (!(strlen(id) && strlen(major) && strlen(grade) && strlen(cals)) {
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

}
void teacherOperate(courseList *cl, studentinformation stu)
{
    bool quit = false;
    char temp[200];
    int cmd;
    while(!quit)
    {
        cmd = t_menu();
        switch(cmd)
        {
        case 0:
            insertstudent(stu, addStudent());
            break;
        }
    }
}
