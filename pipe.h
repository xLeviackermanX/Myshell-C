#ifndef __PIPE_H
#define __PIPE_H
int ifpipe(char *s);
int sepcom(char *s, char **arg);
int ex(int in , int out);
int pipeline(char **arg , int size);

#endif