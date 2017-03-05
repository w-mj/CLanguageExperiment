#ifndef STUDENTS_INFORMATION_H_INCLUDED
#define STUDENTS_INFORMATION_H_INCLUDED

#define courselist courseList*
#include "courseList.h"

struct student
{
    int id;
    char name[20];
    int courseid[500];
    int password;//密码
    int credit;//已选学分
    int subject;//已选课程数
    unsigned int major;//专业
    int classes;//班级
    int year;//学年
    struct student *next;
};

typedef struct student *studentinformation;

int studentnum;//已注册学生数




studentinformation createstudent(void);//要求id按从小到大的顺序输入;
void writeback(studentinformation head);//要求id按从小到大的顺序输入
studentinformation deletestudent(studentinformation head,int num);//删除第一个结点时有bug
studentinformation insertstudent(studentinformation head,studentinformation stud);
studentinformation findstudent(int num,studentinformation head);//按学号查找学生，返回一个结构体
void printstudent(studentinformation head);
void deletecourse(int id,studentinformation stu,courselist head);//学生删除课程
void findstud(int id,studentinformation head);//查找在此课程里的学生人数和学生名单，输入课程编号。
// 返回值说明：-1为课程人数已满，-2为查无此课，0为选课成功，1为选课成功且学分足够
int chooseclass(int cid,studentinformation stu,courselist head);//学生输入课程编号进行选课；


#endif // STUDENT'S_INFORMATION_H_INCLUDED
