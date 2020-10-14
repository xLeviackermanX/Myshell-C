#include "headers.h"
#include "parse.h"
#include "inbuilt.h"
int parse_command(int in , int out , char *str)
{
	

	char yo[1000];
	strcpy(yo,str);
	char *com;
	com=strtok(yo," ");
	int p;
	
	if(ifpipe(str)==1)
	{

		char *arg[1000];
		int size = sepcom(str,arg);
		//printf("%d\n",size );
		pipeline(arg , size);
		return 0;
	}
	p=if_red(in,out,str);
	if(p==-1 || p==1)
	{	
		
		return 0;
	}
	else if(com==NULL || strlen(com)==1)
	{
		return 0;
	}
	else if(strcmp(com,"cd")==0)
	{
		ll i=0;
		while(com!=NULL)
		{
			com=strtok(NULL," ");
			if(com!=NULL)
				i++;
		}
		if(i==0)
			return 0;
		else if(i>1)
		{
			printf("Too many arguments for cd command\n");
			return -1;
		}
		com=strtok(str," ");
		com=strtok(NULL," ");
		cd(com);
	}
	else if(strcmp(com,"ls")==0)
	{
		ls(in,out,str);
	}
	else if(strcmp(com,"jobs")==0)
	{
		jobs(in ,out);
	}
	else if(strcmp(com,"kjob")==0)
	{
		kjobs(str);
	}
	else if(strcmp(com,"echo")==0)
	{
		echo(in,out,str);
	}
	else if(strcmp(com,"pinfo")==0)
	{
		pinfo(in ,out ,str);
	}
	else if(strcmp(com,"setenv")==0)
	{
		set(str);
	}
	else if(strcmp(com,"unsetenv")==0)
	{
		unset(str);
	}
	else if(strcmp(com ,"fg")==0)
	{
		fg(str);
	}
	else if(strcmp(com,"bg")==0)
		bg_(str);
	else if(strcmp(com,"overkill")==0)
		overkill();
	else
	{
		ll check=0;
		while(com!=NULL)
		{
			com=strtok(NULL," ");
			if(com!=NULL)
			{
			if(strcmp(com,"&")==0)
				check=1;
			}
		}
		if(check==0)
			foreground(in ,out ,str);
		else
		{
			
			background(in,out,str);
		}
	}
	//x=strtok(NULL,";");
	//printf("%s\n",x );
	return 0;

}