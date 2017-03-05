#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"courseList.h"
void addCourse(courseList *clist,courseList *head)
{
    courseList *p;
    p=head;
    if(p!=NULL)
    {
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=(courseList*)malloc(sizeof(courseList));
        p=p->next;
    }
    p->id=clist->id;
     strcpy(p->name,clist->name);
     strcpy(p->teacherName,clist->teacherName);
     p->credit=clist->credit;
     p->hours=clist->hours;
     p->maxStudent=clist->maxStudent;
     p->student=clist->student;
     p->major=clist->major;
     p->type=clist->type;
     p->grade=clist->grade;
     p->next=NULL;
     return;
}
/////////////////////
void removeCourse(courseList *clist,courseList *head)
{
    courseList *p,*q;
    p=head;

    if(head->id==clist->id)
    {
       // printf("o1k\n");
       head=head->next;
    }
    else
    {
        q=p->next;
         while(q->id!=clist->id)
        {
            p=q;
            q=q->next;
        }
        p->next=q->next;
        free(clist);
    }

    return;
}
///////////////////////
void readCourseListFromFile(const char *fname,courseList *clist)
{
    FILE *fp;
    fp=fopen(fname,"r+");
    courseList *p,*q;
    p=clist;
    fscanf(fp,"%d",&p->id);
    fscanf(fp,"%s",p->name);
    fscanf(fp,"%s",p->teacherName);
    fscanf(fp,"%d%d%d%d%u%d%d",&p->credit,&p->hours,&p->maxStudent,&p->student,&p->major,&p->type,&p->grade);

    p->next=q;

//printf("ok\n");
while(1)
{
    q=initCourseList();
    if(fscanf(fp,"%d",&q->id)!=EOF)
    {

        p->next=q;
        fscanf(fp,"%s",q->name);
        fscanf(fp,"%s",q->teacherName);
        fscanf(fp,"%d%d%d%d%u%d%d",&q->credit,&q->hours,&q->maxStudent,&q->student,&q->major,&q->type,&q->grade);
       // printf("%d\n",q->id);
        p=q;
        q=q->next;
    }
    else
    {
        p->next=NULL;
        break;
    }

}
    fclose(fp);
    return;
}
/////////////////////
courseList *searchCourse(const char *name,courseList *clist)
{
    courseList *p;
    p=clist;
    while(p!=NULL)
    {
   // printf("name==%s\n",p->name);
        if(strcmp(name,p->name)==0)
            break;
        else
            p=p->next;
    }
    return p;
}

//////////////////
courseList *initCourseList(void)
{
    courseList *p;
    p=(courseList*)malloc(sizeof(courseList));
    return p;
}
//////////////
void destroyCourseList(courseList *clist)
{
    courseList *p,*q;
    //p=initCourseList();
    p=clist;
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    return;
}
courseList *lastcourse(courseList *clist,courseList *head)
{
    courseList *p;
    p=head;
    if(clist->id==head->id)
        return(NULL);
    else
        while(p->next->id!=clist->id)
            {
                p=p->next;
            }
            return p;
}
void printCourse(const char *fname,courseList *head)
{
    FILE *fp;
    fp=fopen(fname,"w+");
    courseList *q;
    q=head;
    while(q!=NULL)
    {
        fprintf(fp,"%d %s %s %d %d %d %d %u %d %d\n",q->id,q->name,q->teacherName,q->credit,q->hours,q->maxStudent,q->student,q->major,q->type,q->grade);
        q=q->next;
    }
    fclose(fp);
    return;
}
