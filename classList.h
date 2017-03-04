#ifndef CLASELIST_H_INCLUDED
#define CLASELIST_H_INCLUDED

// 必修， 选修， 专业
enum ClassType {required, selective, specialize};

struct CLASS {
    char name[20];
    char teacherName[20];
    int id;
    int credit; // 学分
    int hours; // 学时
    int maxStudent;
    int student;
    unsigned int major; // 专业
    enum ClassType type;
    struct CLASS *next;
};

typedef struct CLASS *classList;

classList initClassList(void);   // 初始化
classList searchClass(classList clist, const char * name);  // 按名字查找一门课，返回指向这门课的指针，未找到返回NULL
void readClassListFromFile(classList clist, const char * fname);  // 从文件中读取课程列表
void addClass(classList clist);  // 添加一门课
void removeClass(classList clist);  // 删除一门课
void destroyClassList(classList clist);   // 销毁课程列表

#endif // CLASELIST_H_INCLUDED
