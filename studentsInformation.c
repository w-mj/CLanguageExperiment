#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"studentsInformation.h"
#include "courseList.h"


int studentnum;//已注册学生数

studentinformation createstudent(void)//要求id按从小到大的顺序输入
{
    studentinformation head,p1,p2;
    studentnum=0;
    int i=0,j=0;

    p1=p2=(studentinformation)malloc(sizeof(struct student));
    for(i=0;i<50;i++)
        p1->courseid[i]=0;
    FILE *fp;
    if((fp=fopen("1.txt","r+"))==NULL)
    {
        printf("can not open\n");
        exit(0);
    }

    fscanf(fp,"%d%s%u%d%d%d",&p1->id,p1->name,&p1->major,&p1->classes,&p1->year,&p1->password);
    head=NULL;
    while(p1->id!=0)
    {
        studentnum++;

        p1->credit=0;
        p1->subject=0;
        if(studentnum==1)head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(studentinformation)malloc(sizeof(struct student));
        for(i=0;i<50;i++)
        p1->courseid[i]=0;

    fscanf(fp,"%d%s%u%d%d%d",&p1->id,p1->name,&p1->major,&p1->classes,&p1->year,&p1->password);
    }
    p2->next=NULL;
    return (head);
}

 void writeback(studentinformation head)//要求id按从小到大的顺序输入
{
    studentinformation p1;
    FILE *fp;
    p1=head;
    while(p1!=NULL)
    {
        fprintf(fp,"%d%s%u%d%d%d",p1->id,p1->name,p1->major,p1->classes,p1->year,p1->password);
        p1=p1->next;
    }
}

studentinformation deletestudent(studentinformation head,int num)//删除第一个结点时有bug
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

studentinformation findstudent(int num,studentinformation head)//按学号查找学生，返回一个结构体
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

void deletecourse(int id,studentinformation stu,courselist head)//学生删除课程
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
            stu->courseid[i]=0;
        stu->credit=stu->credit-p1->credit;
        stu->subject--;

    }
}


void findstud(int id,studentinformation head)//查找在此课程里的学生人数和学生名单，输入课程编号。
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


int chooseclass(int cid,studentinformation stu,courselist head)//学生输入课程编号进行选课；
{
    courselist p1,p2;
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
        stu->courseid[stu->subject]=cid;
        stu->subject++;
        stu->credit+=p1->credit;
        if(stu->credit>50)
            return 1; //当学生的学分大于50时，提醒学生学分已经足够。

    }
    if(p1->next==NULL)
        return -2;
    return 0;
}

