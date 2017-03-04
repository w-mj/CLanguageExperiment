#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

unsigned short LastColor;

void initConsole(void);
void gotoxy(int x, int y);
void setColor(unsigned short);
void setTempColor(unsigned short);
void resumeColor(void);
void clearColor(void);
void clearScreen(void);
void hideCursor(void);
void showCursor(void);
void destroyConsole(void);

#endif // CONSOLE_H_INCLUDED
