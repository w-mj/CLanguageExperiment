#include <stdio.h>
#include "courseList.h"

courseList *initCourseList(void)
{
    courseList *p;
    p=(courseList*)malloc(sizeof(courseList));
    return p;
}

void readCourseListFromFile(courseList *clist, const char *fname)
{
    int i=0;
    FILE *fp;
    fp=fopen(fname,"r+");
    courseList *p,*q;
    p=clist;
    fscanf(fp,"%s",p->name);
    fscanf(fp,"%s",p->teacherName);
    fscanf(fp,"%d%d%d%d%d%u%d",&p->id,&p->credit,&p->hours,&p->maxStudent,&p->student,&p->major,&p->type);
    p->next=q;
    while(1)
    {
        q=initCourseList();
        if(fscanf(fp,"%s",q->name)!=EOF)
        {
            p->next=q;
            fscanf(fp,"%s",q->teacherName);
            fscanf(fp,"%d%d%d%d%d%u%d",&q->id,&q->credit,&q->hours,&q->maxStudent,&q->student,&q->major,&q->type);
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
