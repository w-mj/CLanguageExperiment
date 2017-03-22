#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"courseList.h"
#include <conio.h>
void addCourse(courseList *clist, courseList *head)
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
        memset(p -> next, 0, sizeof(courseList));
        p=p->next;
    } else {
        p = (courseList*)malloc(sizeof(courseList));
        memset(p, 0, sizeof(courseList));
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
    if (clist == NULL ||head == NULL)
        return ;
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
    fscanf(fp,"%d%d%d%d%u%d%d%d",&p->credit,&p->hours,&p->maxStudent,&p->student,&p->major,&p->type,&p->grade,&p->time);
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
        fscanf(fp,"%d%d%d%d%u%d%d%d",&q->credit,&q->hours,&q->maxStudent,&q->student,&q->major,&q->type,&q->grade,&q->time);
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
/*
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
*/

//////////////////
courseList *initCourseList(void)
{
    courseList *p;
    p=(courseList*)malloc(sizeof(courseList));
    memset(p, 0, sizeof(courseList));
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
courseList *lastcourse(int id,courseList *head)
{
    courseList *p;
    p=head;
    if(id==head->id)
        return(NULL);
    else
        while(p->next->id!=id)
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
        fprintf(fp,"%d %s %s %d %d %d %d %u %d %d %d\n",q->id,q->name,q->teacherName,q->credit,q->hours,q->maxStudent,q->student,q->major,q->type,q->grade, q -> time);
        q=q->next;
    }
    fclose(fp);
    return;
}

char* searchCourseA(char *space, courseList *head, int id)
{
    memset(space, 0, sizeof(TEMP_STRING));
    while (head != NULL) {
        if (head -> id == id) {
            strcpy(space, head -> name);
            return space;
        }
        head = head -> next;
    }
    return space;
}

char* searchCourse(courseList *head, int id)
{
    return searchCourseA(TEMP_STRING, head, id);
}

courseList *majorsearch(int major,int grade,int type,courseList *head)
{
    courseList *a,*p;
    a=initCourseList();
    p=head;
    while(p!=NULL)
    {
        if(((p->major&major)||major==-1)&&((grade==p->grade)||(grade==-1)||(p->grade==0))&&(type==p->type)||(type==-1))
            addCourse(p,a);
        p=p->next;
    }
    p = a;
    a = a -> next;
    free(p);
    return a;
}

courseList *searchCourseByID(courseList *clist, int id)
{
    if (clist == NULL)
        return NULL;
    while (clist != NULL) {

        if (clist -> id == id)
            return clist;
        else clist = clist -> next;
    }
    return NULL;
}

courseList *namesearch(const char *name,courseList *clist)
{
    int i,j,k=0,flag,m,e=0;
    courseList *p,*a;
    a=initCourseList();
    p=clist;
    char c[20];
   // printf("name==%s\n",p->name);
    strcpy(c,name);
        while(p!=NULL)
        {
           int n=strlen(p->name);

           for(i=0;i<n;i++)
           {
               j=0;
               flag=0;
               m=strlen(c);
               k=i;
               for(j=0;j<m;j++,k++)
               {
                    if(p->name[k]!=c[j])
                    {
                        flag=1;
                        break;
                    }
               }
               if(flag==0)
               {
                   addCourse(p,a);
                   e++;
                    break;
               }
           }
           p=p->next;
        }
        if(e==0)
            return NULL;
        else
         return a;
    }
