#ifndef STUDENTS_INFORMATION_H_INCLUDED
#define STUDENTS_INFORMATION_H_INCLUDED

#define courselist courseList*
#include "courseList.h"

struct student
{
    int id;
    char name[20];
    int courseid[500];
    int password;//����
    int credit;//��ѡѧ��
    int subject;//��ѡ�γ���
    unsigned int major;//רҵ
    int classes;//�༶
    int year;//ѧ��
    struct student *next;
};

typedef struct student *studentinformation;

int studentnum;//��ע��ѧ����




studentinformation createstudent(void);//Ҫ��id����С�����˳������;
void writeback(studentinformation head);//Ҫ��id����С�����˳������
studentinformation deletestudent(studentinformation head,int num);//ɾ����һ�����ʱ��bug
studentinformation insertstudent(studentinformation head,studentinformation stud);
studentinformation findstudent(int num,studentinformation head);//��ѧ�Ų���ѧ��������һ���ṹ��
void printstudent(studentinformation head);
void deletecourse(int id,studentinformation stu,courselist head);//ѧ��ɾ���γ�
void findstud(int id,studentinformation head);//�����ڴ˿γ����ѧ��������ѧ������������γ̱�š�
// ����ֵ˵����-1Ϊ�γ�����������-2Ϊ���޴˿Σ�0Ϊѡ�γɹ���1Ϊѡ�γɹ���ѧ���㹻
int chooseclass(int cid,studentinformation stu,courselist head);//ѧ������γ̱�Ž���ѡ�Σ�


#endif // STUDENT'S_INFORMATION_H_INCLUDED
