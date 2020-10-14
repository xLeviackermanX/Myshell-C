#include "headers.h"

int ifpipe(char *s)
{
	ll k=strlen(s);
	ll c=0;
	for(ll i=0;i<k;i++)
	{
		if(s[i]=='|')
		{
			c=1;
			break;
		}
	}
	return c;
} 

int sepcom(char *s , char **arg)
{
	ll i =0;
	arg[i]=strtok(s,"|");
	while(arg[i]!=NULL)
	{
		i++;
		arg[i]=strtok(NULL,"|");
	}
	return i;
}

int ex(int in , int out)
{
	
		if(in)
		{
			dup2(in,0);
			close(in);
		}
		if(out!=1)
		{
			dup2(out , 1);
			close(out);
		}
}

int pipeline(char **arg , int size )
{
	
	int  in=0,f[2];
	for(ll i=0;i<size-1;i++)
	{
		pipe(f);
		char str[1000];
		strcpy(str,arg[i]);
		parse_command(in,f[1],str);
		close(f[1]);
		in=f[0];
	}

	
	char str[1000];
	strcpy(str , arg[size-1]);
	parse_command(in,1,str);
	return 0;
		
}