#include "headers.h"
#include "background.h"

int background(int in  , int out, char * str)
{
	char *arg[1000];
	char *ch = strtok(str," ");
	ll i=0;
	while(strcmp(ch,"&")!=0)
	{
		arg[i]=ch;
		i++;
		ch = strtok(NULL," ");
	}
	
	arg[i]=NULL;
	
	int a;
	int f = fork();
	
	if(f==0)
	{
		signal(SIGINT , SIG_DFL);
		ll yo = getpid();
		setpgid(yo,yo);
		ex(in , out);
		
		execvp(arg[0],arg);

		
		//printf("\n%s with pid %lld exited normally",arg[0] , pid );		
		exit(0);
	}
	else
	{
		signal(SIGINT , SIG_IGN);
		setpgid(f,f);
		tcsetpgrp(STDIN_FILENO, getpgid(getpid()));
		for(ll i=0;i<1000;i++)
		{
			if(bg[i]==-1)
			{
				bg[i]=f;
				strcpy(pro[i],arg[0]);
				break;
			}
		}
		
		//waitpid(-1,&a,WNOHANG);
	}

	return 0;
}
