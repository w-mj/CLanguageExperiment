#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"student's information"
struct COURSE {
    char name[20];
    char teacherName[20];
    int id;
    int credit; // ѧ��
    int hours; // ѧʱ
    int maxStudent;
    int student;
    unsigned int major; // רҵ
    enum CourseType type;
    struct COURSE *next;
};

typedef struct COURSE *courseList;

struct student
{
    int id;
    char name[20];

    int password;//����
    int credit;//��ѡѧ��
    int subject;//��ѡ�γ���
    unsigned int major;//רҵ
    int classes;//�༶
    int year;//ѧ��
    struct student *next;
};

int studentnum;//��ע��ѧ����
typedef struct student *studentinformation;

studentinformation createstudent(void)//Ҫ��id����С�����˳������
{
    studentinformation head,p1,p2;
    studentnum=0;
    p1=p2=(studentinformation)malloc(sizeof(struct student));
    scanf("%d%s%u%d%d",&p1->id,p1->name,&p1->major,&p1->classes,&p1->year);
    head=NULL;
    while(p1->id!=0)
    {
        studentnum++;
        p1->password=p1->id;
        p1->credit=0;
        p1->subject=0;
        if(studentnum==1)head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(studentinformation)malloc(sizeof(struct student));
        scanf("%d%s%u%d%d",&p1->id,p1->name,&p1->major,&p1->classes,&p1->year);
    }
    p2->next=NULL;
    return (head);
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

