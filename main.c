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
    int cmd;
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
    readCourseListFromFile("Users.txt", courseList);

    currentStudent = login(studentList);
    while(!quit) {

        cmd = menu();
        switch(cmd) {
            case 0:
                election(courseList, currentStudent);
                break;
            case 3:
                printSyllabus();
                break;
            case 4:
                quit = true;
                break;
        }


    }
    clearColor();
    gotoxy(0, 0);
    destroyConsole();
    return 0;
}
