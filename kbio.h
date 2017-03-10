#ifndef KBIO_H_INCLUDED
#define KBIO_H_INCLUDED

enum StringType { text, number, password, chinese};
unsigned int getKeyboard(void);
int getString(unsigned char * content, enum StringType type,int start, int length);

#endif // KBIO_H_INCLUDED
