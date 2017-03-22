#include "kbio.h"
#include <ctype.h>
#include <conio.h>
#include <stdio.h>

unsigned int getKeyboard(void)
{
    unsigned int ch;
    unsigned int ret = 0;
    ch = getch();
    //printf("**");
    //printf("%d\n", ch);
    if (ch & 0x80) {
        // 如果最高位是1 再读一位
        ret = ch << 8;
        ch = getch();
        ret += ch;
    } else {
        ret = ch;
    }
    //gotoxy(0, 0);
    //printf("%x\n", ret);
    return ret;
}

int getString(unsigned char * content, enum StringType type, int start, int length)
{
    int count = start;
    unsigned int ch;
    if (type == chinese) {
        scanf("%s", content); // TODO
    } else {
        while (count <= length) {
            ch = getKeyboard();
            //clearMsg();
            //printf("%x\n", ch);
                if (ch == 9 || ch == 13 ||
                (ch & 0xff00) && (((ch & 0x00ff) == 80) || ((ch & 0x00ff) == 72) || ((ch & 0x00ff) == 75 ) || ((ch & 0x00ff) == 77)))
            { // 遇控制字符 直接返回

                content[count] = '\0';
                return ch;
            }

            if (ch == 8 && count > 0) {
                // 退格
                printf("\b \b");
                count -= 1;
            }

            if (count == length)
                continue;

            if (type == chinese) {
                if (isalnum(ch)) {
                    putchar(ch);
                    content[count++] = ch;
                } else {
                    putchar((ch & 0xff00) >> 8);
                    putchar(ch & 0x00ff);
                    content[count++] = (ch & 0xff00) >> 8;
                    content[count++] = ch;
                }
            } else if (type == text) {
                if (isalnum(ch)) {
                    putchar(ch);
                    content[count++] = ch;
                }
            } else if (type == number) {
                if (isdigit(ch)) {
                    putchar(ch);
                    content[count++] = ch;
                }
            } else if (type == password) {
                if (isprint(ch)) {
                    putchar('*');
                    content[count++] = ch;
                }
            }
        }
        content[count] = '\0';
    }
    return 0;
}
