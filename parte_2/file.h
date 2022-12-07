#include <sys/time.h>
#include <time.h>

void open_file(char [], char [], int);
void read_file_text(char *, char *);
int read_file_text2(char *, int *, int *);
int read_file_pattern(char *);
void close_file();
void output1();
void output2(char *s);
void output3(long d);
double time_diff(struct timeval *start, struct timeval *end);