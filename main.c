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
    char temp[1000];
    //setColor(0x0f);

    courseList * clist = NULL;
    studentinformation studentList = NULL;
    studentinformation currentStudent = NULL;
    clist = initCourseList();
    studentList = createstudent();
    readCourseListFromFile("course.txt", clist);


    //getch();
    currentStudent = login(studentList);
    while(!quit) {

        cmd = menu(currentStudent);
        switch(cmd) {
            case 0:
                while(1) {
                    courseID = election(clist, currentStudent);
                    if (courseID == -1)
                        break;
                    if (currentStudent -> id == 0) {
                        dialog("教师不能选课");
                        continue;
                    }
                    strcpy(temp, "你确定要选择：");
                    strcat(temp, searchCourse(clist, courseID));
                    strcat(temp, "  吗？");

                    if (confirm(temp)) {
                        ret = chooseclass(courseID, currentStudent, clist);
                        switch(ret) {
                        case -2:
                            dialog("选课失败，无此课程");
                            break;
                        case -1:
                            dialog("该门课程人数已满");
                            break;
                        case 0:
                            dialog("选课成功");
                            break;
                        case 1:
                            dialog("选课成功，您的学分已经足够");
                            break;
                        case 2:
                            dialog("您已经选过该门课程，请勿重复选课");
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
                    teacherOperate(currentStudent, clist);
                break;
            case 4:
                quit = true;
                break;
        }
        //while(getchar() != '\n');

    }
    writeback(studentList);
    clearColor();
    gotoxy(0, 0);
    destroyConsole();
    return 0;
}
