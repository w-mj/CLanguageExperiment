#ifndef CLASELIST_H_INCLUDED
#define CLASELIST_H_INCLUDED

char TEMP_STRING[1000];

// 必修， 选修， 专业
enum CourseType {required, selective, specialize};

typedef struct COURSE {
    int id;
    char name[20];
    char teacherName[20];
    int credit; // 学分
    int hours; // 学时
    int maxStudent;
    int student;
    unsigned int major; // 专业
    enum CourseType type;
    int grade;
    int time;//上课时间：如周一第一节、周二第二节表示为1122
    struct COURSE *next;
}courseList;

//typedef struct COURSE *courseList;

courseList *initCourseList(void);   // 初始化
//courseList *searchCourse( const char * name,courseList *clist);  // 按名字查找一门课，返回指向这门课的指针，未找到返回NULL
void readCourseListFromFile( const char * fname,courseList *clist);  // 从文件中读取课程列表
void addCourse(courseList *clist,courseList *head);  // 添加一门课
void removeCourse(courseList *clist,courseList *head);  // 删除一门课,按id查找
void destroyCourseList(courseList *clist);   // 销毁课程列表
void printCourse(const char *fname,courseList *head);//输出课程列表到文件中
courseList *lastcourse(int id,courseList *head);//返回前一个指针,若目标为头指针则返回NULL
char* searchCourse(courseList *head, int id);
courseList *majorsearch(int major,int grade,int type,courseList *head);//按专业和年级查找
courseList *searchCourseByID(courseList *clist, int id);
courseList *namesearch( const char * name,courseList *clist);  // 按名字查找一门课，返回指向这门课的指针，未找到返回NULL


#endif // CLASELIST_H_INCLUDED
