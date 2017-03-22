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
                            getch();
                            if (confirm("您已经选过该门课程，是否要删除这门课"))
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
