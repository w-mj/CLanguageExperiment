#ifndef CLASELIST_H_INCLUDED
#define CLASELIST_H_INCLUDED

// ���ޣ� ѡ�ޣ� רҵ
enum ClassType {required, selective, specialize};

struct CLASS {
    char name[20];
    char teacherName[20];
    int id;
    int credit; // ѧ��
    int hours; // ѧʱ
    int maxStudent;
    int student;
    unsigned int major; // רҵ
    enum ClassType type;
    struct CLASS *next;
};

typedef struct CLASS *classList;

classList initClassList(void);   // ��ʼ��
classList searchClass(classList clist, const char * name);  // �����ֲ���һ�ſΣ�����ָ�����ſε�ָ�룬δ�ҵ�����NULL
void readClassListFromFile(classList clist, const char * fname);  // ���ļ��ж�ȡ�γ��б�
void addClass(classList clist);  // ���һ�ſ�
void removeClass(classList clist);  // ɾ��һ�ſ�
void destroyClassList(classList clist);   // ���ٿγ��б�

#endif // CLASELIST_H_INCLUDED
