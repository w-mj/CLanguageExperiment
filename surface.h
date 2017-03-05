#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "courseList.h"
#include "studentsInformation.h"


studentinformation login(studentinformation stul);
int election(courseList * clist, studentinformation cstudent);
int menu(void);
void printSyllabus();

#endif // SURFACE_H_INCLUDED
