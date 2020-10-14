#include "headers.h"
void seg_handler(int sig)
{
    if(cur_pid!=-1)
    {
        kill(cur_pid , SIGSTOP);
        x=1;
    }

}
void s_handler(int sig)
{
	if(cur_pid!=-1)
	{
		kill(cur_pid , SIGKILL);
	}
}
int jobs(int in , int out)
{
	for(ll i=0;i<1000;i++)
	{
		if(bg[i]==-1)
			continue;
		char check[1024];
		sprintf(check,"[%lld]  ", i+1);
		write(out,check ,strlen(check));
		char path[1000];
	sprintf(path ,"/proc/%d/status",bg[i]);
	FILE *f= fopen(path,"r");
	if(!f)
	{
		printf("error in opening status file of pid %d\n",bg[i]);
		return -1;
	}
	long unsigned int size = 1000;
	char *s;char *name;
	name = (char *)malloc(size);
	s = (char *)malloc(size);
	char state;
	getline(&s,&size, f);
	sscanf(s,"Name: \t%s",name);
	//printf("%s\n",s );	
	getline(&s,&size, f);
	//printf("%s\n", s);
	getline(&s,&size, f);
	//printf("%s\n", s);
	sscanf(s,"State: \t%c",&state);
	if(state=='T')
		write(out ,"Stopped  ",sizeof("Stopped  "));
	else
		write(out , "Running  ", sizeof("Running  "));
	sprintf(check ,"%s  %d\n",name,bg[i]);
	write(out,check ,strlen(check));
	}
	return 0;
}

int kjobs(char *s)
{
	char *arg[1000];
	int n = split(s,arg);
	if(n!=3)
	{
		printf("Wrong number of arguments for kjobs command\n");
		return -1;
	}
	int pid=0 , sig=0;
	ll k=strlen(arg[1]);
	ll h=1;
	for(ll i=k-1;i>=0;i--)
	{
		pid+= (int)(arg[1][i]-'0');
		h*=10;
	}
	if(pid>0 && pid<1000)
	{
	if(bg[pid-1]==-1)
	{
		printf("No process is running with given id\n");
		return -1;
	}
	h=1;
	k=strlen(arg[2]);
	for(ll i=k-1;i>=0;i--)
	{
		sig+=(int)(arg[2][i]-'0');
		h*=10;
	}
	setpgid(bg[pid-1],getpid());
	//tcsetpgrp(STDIN_FILENO,bg[pid-1]);
	int p = kill(bg[pid-1],sig);
	printf("%d\n",p );
	if(p==-1)
	{
		perror("");
		return -1;
	}

	}
	else
		printf("invalid id\n");
	return 0;
}

int fg(char *str)
{
	char *arg[100];
	int a=split(str,arg);
	if(a!=2)
	{
		printf("Wrong number of arguments for fg command\n");
		return -1;
	}
	int pid=0;
	ll k=strlen(arg[1]);
	ll h=1;
	for(ll i=k-1;i>=0;i--)
	{
		pid+= (int)(arg[1][i]-'0');
		h*=10;
	}
	if(pid<1 || pid>=1000 || bg[pid-1]==-1)
	{
		printf("process with given id %d does not exist\n",pid);
		return 0;
	}
	int i=pid-1;
	if(kill(getpgid(bg[i]),SIGCONT)==-1)
	{
		perror("");
		return -1;
	}
	if(tcsetpgrp(0,getpgid(bg[i]))==-1)
	{
		perror("");
		return -1;
	}
	 signal(SIGINT,s_handler);
        signal(SIGTSTP , seg_handler);
        cur_pid=bg[i];
        while(1)
        {
            int a;
            int b = waitpid(cur_pid,&a,WNOHANG);

            if(b!=0)
                break;
            if(x==1)
            {
                x=0;
                break;
            }

        }

        cur_pid=-1;
	signal(SIGTTOU , SIG_IGN);
	tcsetpgrp(0,getpgid(getpid()));
	signal(SIGTTOU , SIG_DFL);
	return 0;
}


int bg_(char *str)
{
	char *arg[100];
	int a=split(str,arg);
	if(a!=2)
	{
		printf("Wrong number of arguments for fg command\n");
		return -1;
	}
	int pid=0;
	ll k=strlen(arg[1]);
	ll h=1;
	for(ll i=k-1;i>=0;i--)
	{
		pid+= (int)(arg[1][i]-'0');
		h*=10;
	}
	if(pid<1 || pid>=1000 || bg[pid-1]==-1)
	{
		printf("process with given id %d does not exist\n",pid);
		return 0;
	}
	pid--;
	if(kill(bg[pid],SIGCONT)==-1)
	{
		perror("");
		return -1;
	}
	return 0;
}

int overkill()
{
	for(ll i=999;i>=0;i--)
	{
		if(bg[i]==-1)
			continue;
		if(kill(bg[i],9)==-1)
		{
			printf("error in killing process with pid %d:  ",bg[i] );
			perror("");
		}
		bg[i]=-1;
	}
	return 0;
}