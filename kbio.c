#include "kbio.h"
#include <ctype.h>
#include <conio.h>

int getKeyboard(void)
{
    int ch;
    ch = getch();
    //printf("%d\n", ch);
    if (ch == 224) // 方向键等特殊字符
        ch = -getch();
    //printf("%d\n", ch);
    return ch;
}

int getString(char * content, enum StringType type, int start, int length)
{
    int count = start;
    int ch;
    while (count <= length) {
        ch = getKeyboard();
        if (ch == 8) {
            // 退格
            printf("\b \b");
            count -= 1;
        }

        if (ch == 9 || ch == -80 || ch == 13 || ch == -72) {
            content[count] = '\0';
            return ch;
        }
        if (count == length)
            continue;
        if (type == text) {
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
    return 0;
}
