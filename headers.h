#include<stdio.h>
#include "parse.h"
#include "pipe.h" 
#include<sys/utsname.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/wait.h>
#include "foreground.h"
#include "background.h"
#include "pinfo.h"
#include<sys/types.h>
#include<fcntl.h>
#include "variable.h"
#include "jobs.h"
#include "redirect.h"
#include<signal.h> 

char shell_path[1000];
int shell_pid;
int bg[1000];
char pro[1000][1000];
char cur_com[1000];
int cur_pid;
int x;
#define ll long long int