#include "headers.h"

int pinfo(int in , int out ,char *str)
{
	char *p = strtok(str," ");
	p  = strtok(NULL , " ");
	int pid;
	if(p==NULL)
	{
		pid = getpid();
	}
	else
	{
		pid=0;
		ll k=strlen(p);
		ll h=1;
		for(ll i=k-1;i>=0;i--)
		{
			pid+=h*(p[i]-'0');
			h*=10;
		}
	}
	char check[1024];
	sprintf(check ,"pid -- %d\n",pid );
	write(out,check ,strlen(check));
	char path[1000];
	sprintf(path ,"/proc/%d/status",pid);
	FILE *f= fopen(path,"r");
	if(!f)
	{
		perror("error in opening status file of given pid\n");
		return -1;
	}
	long unsigned int size = 1000;
	char *s;
	s = (char *)malloc(size);
	//name=(char  *)malloc(size);
	char state;
	getline(&s,&size, f);
//	sscanf(s,"Name: \t%s",name);
	//printf("%s\n",s );	
	getline(&s,&size, f);
	//printf("%s\n", s);
	getline(&s,&size, f);
	//printf("%s\n", s);
	sscanf(s,"State: \t%c",&state);
	sprintf(check ,"Process Status -- %c\n",state );
	write(out,check ,strlen(check));
	sprintf(path ,"/proc/%d/statm",pid);
	fclose(f);
	f=fopen(path , "r");
	if(!f)
	{
		perror("error in opening statm file of given pid\n");
		return -1;
	}
	getline(&s,&size, f);
	char *x=strtok(s," ");
	sprintf(check ,"Memory -- %s\n",x );
	write(out,check ,strlen(check));
	fclose(f);
	sprintf(path ,"/proc/%d/exe",pid);
	int l = readlink(path ,s,1000);
	if(l<0)
	{
		perror("error in opening exe file of given pid\n");
		return -1;
	}
	s[l]='\0';
	sprintf(check ,"Executable path -- %s\n",s);
	write(out,check ,strlen(check));
	return 0;
}