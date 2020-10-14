#include "headers.h"

int split(char *s, char **arg)
{
	arg[0]=strtok(s," ");
	ll i=0;
	while(arg[i]!=NULL)
	{
		i++;
		arg[i] = strtok(NULL," ");
	}
	return i;
}

int set(char *s)
{
	char *arg[1000];
	int num = split(s,arg);
	if(num<2 || num>3)
	{
		printf("Wrong number of arguments for setenv command\n");
		return -1;
	}
	if(arg[2]!=NULL)
	{
		if(setenv(arg[1],(const char *)arg[2] ,1)==-1)
		{
			perror("");
			return -1;
		}
	}
	else
	{
		if(setenv(arg[1],"",1)==-1)
		{
			perror("");
			return -1;
		}
	}
	return 0;
}

int unset(char *s)
{
	char *arg[1000];
	int num = split(s,arg);
	if(num!=2)
	{
		printf("Wrong number of arguments for unsetenv command\n");
		return -1;
	}
	if(unsetenv(arg[1])==-1)
	{
		perror("");
		return -1;
	}
	return -1;
}