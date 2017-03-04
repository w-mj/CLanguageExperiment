#include "console.h"
#include "kbio.h"
#include "graph.h"
#include "surface.h"
#include "courseList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 123

int main(void)
{
    initConsole();
    hideCursor();
    clearColor();

    courseList * courseList;
    courseList = initCourseList();
    readCourseListFromFile("Users.txt", courseList);

    clearColor();
    //login();

    setColor(0xb1);
    drawFrame();
    election(courseList);
    clearColor();
    gotoxy(0, 30);
    destroyConsole();
    return 0;
}
