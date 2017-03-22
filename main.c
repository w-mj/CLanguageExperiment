#include "console.h"
#include "kbio.h"
#include "graph.h"
#include "surface.h"
#include "courseList.h"
#include "studentsInformation.h"
#include "teacherOperate.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

int main(void)
{
    int cmd, courseID, ret;
    bool quit = false;
    initConsole();
    hideCursor();
    clearColor();
    clearScreen();
    char temp[100];
    //setColor(0x0f);

    courseList * clist = NULL;
    studentinformation studentList = NULL;
    studentinformation currentStudent = NULL;
    studentList = createstudent();
    clist = initCourseList();
    readCourseListFromFile("course.txt", clist);


    //getch();
    currentStudent = login(studentList);
    while(!quit) {

        cmd = menu(currentStudent);
        setColor(BASIC_COLOR);
        switch(cmd) {
            case 0:
                while(1) {
                    setColor(BASIC_COLOR);
                    courseID = election(clist, currentStudent);
                    while(kbhit())
                        getch();
                    if (courseID == -1)
                        break;
                    if (currentStudent -> id == 0) {
                        dialog("��ʦ����ѡ��");
                        continue;
                    }
                    strcpy(temp, "��ȷ��Ҫѡ��");
                    strcat(temp, searchCourse(clist, courseID));
                    strcat(temp, "  ��");

                    if (confirm(temp)) {
                        ret = chooseclass(courseID, currentStudent, clist);
                        switch(ret) {
                        case -2:
                            dialog("ѡ��ʧ�ܣ��޴˿γ�");
                            break;
                        case -1:
                            dialog("���ſγ���������");
                            break;
                        case 0:
                            dialog("ѡ�γɹ�");
                            break;
                        case 1:
                            dialog("ѡ�γɹ�������ѧ���Ѿ��㹻");
                            break;
                        case 2:
                            getch();
                            if (confirm("���Ѿ�ѡ�����ſγ̣��Ƿ�Ҫɾ�����ſ�"))
                                deletecourse(courseID, currentStudent, clist);
                            break;
                        default:
                            sprintf(temp, "%d", ret);
                            dialog(temp);
                            break;
                        }
                    }
                }
                break;
            case 1:
                clearScreen();
                showStudentInformation(clist, currentStudent);
                getch();
                break;
            case 2:
                changePsd(currentStudent);
                break;
            case 3:
                if (currentStudent -> id != 0)
                    printSyllabus(clist, currentStudent);
                else
                    teacherOperate(clist, studentList);
                break;
            case 4:
                quit = true;
                break;
        }
        //while(getchar() != '\n');

    }
    writeback(studentList);
    printCourse("course.txt", clist);
    clearColor();
    gotoxy(0, 0);
    destroyConsole();
    return 0;
}
