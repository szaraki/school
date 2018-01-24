#ifndef CLIPBOARD_H
#define CLIPBOARD_H



int initialise(void);

int set(const char* text);

void clean(void);

int append(const char* text);

int count(void);

void printToStdout(void);


#endif