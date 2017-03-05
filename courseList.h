#ifndef CLASELIST_H_INCLUDED
#define CLASELIST_H_INCLUDED

// ���ޣ� ѡ�ޣ� רҵ
enum CourseType {required, selective, specialize};

typedef struct COURSE {
    int id;
    char name[20];
    char teacherName[20];
    int credit; // ѧ��
    int hours; // ѧʱ
    int maxStudent;
    int student;
    unsigned int major; // רҵ
    enum CourseType type;
    int grade;
    struct COURSE *next;
}courseList;

//typedef struct COURSE *courseList;

courseList *initCourseList(void);   // ��ʼ��
courseList *searchCourse( const char * name,courseList *clist);  // �����ֲ���һ�ſΣ�����ָ�����ſε�ָ�룬δ�ҵ�����NULL
void readCourseListFromFile( const char * fname,courseList *clist);  // ���ļ��ж�ȡ�γ��б�
void addCourse(courseList *clist,courseList *head);  // ���һ�ſ�
void removeCourse(courseList *clist,courseList *head);  // ɾ��һ�ſ�,��id����
void destroyCourseList(courseList *clist);   // ���ٿγ��б�
void printCourse(const char *fname,courseList *head);
courseList *lastcourse(courseList *clist,courseList *head);//����ǰһ��ָ��,��Ŀ��Ϊͷָ���򷵻�NULL

#endif // CLASELIST_H_INCLUDED
