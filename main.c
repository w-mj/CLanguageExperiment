#include "console.h"
#include "kbio.h"
#include "graph.h"
#include "surface.h"
#include "courseList.h"
#include "studentsInformation.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    int cmd, courseID, ret;
    bool quit = false;
    initConsole();
    hideCursor();
    clearColor();
    clearScreen();
    //setColor(0x0f);

    courseList * courseList = NULL;
    studentinformation studentList = NULL;
    studentinformation currentStudent = NULL;
    courseList = initCourseList();
    studentList = createstudent();
    readCourseListFromFile("course.txt", courseList);


    //printSyllabus();
    //getch();
    currentStudent = login(studentList);
    while(!quit) {

        cmd = menu();
        switch(cmd) {
            case 0:
                courseID = election(courseList, currentStudent);
                ret = chooseclass(courseID, currentStudent, courseList);
                switch(ret) {
                case -2:
                    errorMsg("ѡ��ʧ�ܣ��޴˿γ̣������������");
                    break;
                case -1:
                    errorMsg("���ſγ����������������������");
                    break;
                case 0:
                    errorMsg("ѡ�γɹ��������������");
                    break;
                case 1:
                    errorMsg("ѡ�γɹ�������ѧ���Ѿ��㹻�������������");
                    break;
                }
                getch();
                break;
            case 1:
                clearScreen();
                showStudentInformation(courseList, currentStudent);
                getch();
                break;
            case 3:
                printSyllabus(courseList, currentStudent);
                break;
            case 4:
                quit = true;
                break;
        }
    }
    writeback(studentList);
    clearColor();
    gotoxy(0, 0);
    destroyConsole();
    return 0;
}
