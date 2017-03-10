#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
#include"studentsInformation.h"
#include "courseList.h"


int studentnum;//��ע��ѧ����

studentinformation createstudent(void)//Ҫ��id����С�����˳������
{
    studentinformation ret = NULL, cursor = NULL;
    FILE* fp = fopen("students.txt", "r+");
    if (fp == NULL) {
        fprintf(stderr, "Fail to open student data.\n");
        exit(10);
    }
    int tempID;
    bool first = true;
    while(~fscanf(fp, "%d", &tempID)) {
        if (first) {
            ret = cursor = (studentinformation)malloc(sizeof(struct student));
            first = false;
        } else {
            cursor -> next = (studentinformation)malloc(sizeof(struct student));
            cursor = cursor -> next;
        }
        cursor -> next = NULL;
        cursor -> id = tempID;
        fscanf(fp, "%s%u%d%d%s%d%d",
               cursor -> name, &cursor -> major, &cursor -> classes, &cursor -> year, &cursor -> password, &cursor -> credit, &cursor -> subject);
        cursor -> endOfCourseArray = cursor -> subject;
        for (int i = 0; i < cursor -> subject; i++) {
            fscanf(fp, "%d", &cursor -> courseid[i]);
        }
    }
    return ret;
}

void writeback(studentinformation head)//Ҫ��id����С�����˳������
{
    studentinformation p1;
    FILE *fp;
    fp = fopen("students.txt", "w");
    p1=head;
    while(p1!=NULL)
    {
        fprintf(fp,"%d %s %u %d %d %s %d %d ",p1->id,p1->name,p1->major,p1->classes,p1->year,p1->password,p1 -> credit, p1->subject);
        int i;
        for(i=0;i<p1->endOfCourseArray;i++) {
            if (p1 -> courseid[i] == 0)
                continue;
            fprintf(fp,"%d ",p1->courseid[i]);
        }
        fprintf(fp, "\n");
        p1=p1->next;
    }
    fclose(fp);
}


studentinformation deletestudent(studentinformation head,int num)//ɾ����һ�����ʱ��bug
{
    studentinformation p1,p2;
    if(head==NULL)
    {
        printf("list NULL!\n");
        return(head);
    }
    else
    {
        p1=head;
        while(num!=p1->id&&p1->next!=NULL)
        {
            p2=p1;
            p1=p1->next;
        }
        if(num==p1->id)
        {
            if(p1==head)head=p1->next;
            else p2->next=p1->next;
            printf("delete students'id:%d\n",num);
            studentnum--;
        }
        else
            printf("can't find this id\n");
        return head;
    }
}

studentinformation insertstudent(studentinformation head,studentinformation stud)
{
    studentinformation p0,p1,p2;
    p1=head;
    p0=stud;
    if(head==NULL)
    {
        head=p0;
        p0->next=NULL;
    }
    else
        while((p0->id>p1->id)&&(p1->next!=NULL))
    {
        p2=p1;
        p1=p1->next;
    }
    if(p0->id<=p1->id)
    {
        if(head==p1)head=p0;
        else p2->next=p0;
        p0->next=p1;
    }
    else
    {
        p1->next=p0;
        p0->next=NULL;
    }
    studentnum++;
    return head;
}

studentinformation findstudent(int num,studentinformation head)//��ѧ�Ų���ѧ��������һ���ṹ��
{
    studentinformation p1;
    p1=head;
    while((p1->id!=num)&&(p1->next!=NULL))
    p1=p1->next;
    if(p1->id==num)
        return p1;
    else
    {
        printf("not find the student id\n");
        return head;

    }

}

void printstudent(studentinformation head)
{
    studentinformation p;
    printf("these  %d records are\n",studentnum);
    p=head;
    while(p!=NULL)
    {
        printf("id:%d name:%s password:%d credit:%d subject:%d major:%d classes:%d year:%d\n",p->id,p->name,p->password,p->credit,p->subject,p->major,p->classes,p->year);
        p=p->next;
    }
}

void deletecourse(int id,studentinformation stu,courselist head)//ѧ��ɾ���γ�
{
    courselist p1=head;
    int i;
    while((p1->id!=id)&&(p1->next!=NULL))
        p1=p1->next;
    if(p1->next==NULL)
        printf("this course is not at here\n");
    if(p1->id==id)
    {
        p1->student--;
        for(i=0;i<stu->subject;i++)
            if(stu->courseid[i]==id)
            stu->courseid[i]=0; // ����ɾ��
        stu->credit=stu->credit-p1->credit;
        stu->subject--;

    }
}


void findstud(int id,studentinformation head)//�����ڴ˿γ����ѧ��������ѧ������������γ̱�š�
{
    studentinformation p1=head;
    int i,flag,num=0;
    while(p1!=NULL)
    {
        for(i=0;i<p1->subject;i++)
        {
            flag=0;
            if(p1 -> courseid[i]==id)
            {
                flag=1;
                num++;
                break;
            }
        }
        if(flag)printf("%d    %s\n",p1->id,p1->name);
    }
    printf("there are %d students in this course\n",num);
}


int chooseclass(int cid,studentinformation stu,courselist head)//ѧ������γ̱�Ž���ѡ�Σ�
{
    courselist p1;
    p1=head;
    while((p1->id!=cid)&&(p1->next!=NULL))
        p1=p1->next;
    if(p1->id==cid)
    {
        p1->student++;
        if(p1->student>p1->maxStudent) {
            p1 -> student -= 1;
            return -1;
        }
        for (int i = 0; i < stu -> subject; i++) {
            if (stu -> courseid[i] == cid)
                return 2;
        }
        stu->courseid[stu->subject]=cid;
        stu->subject++;
        stu -> endOfCourseArray++;
        stu->credit+=p1->credit;
        if(stu->credit>50)
            return 1; //��ѧ����ѧ�ִ���50ʱ������ѧ��ѧ���Ѿ��㹻��

    }
    if(p1->next==NULL)
        return -2;
    return 0;
}

