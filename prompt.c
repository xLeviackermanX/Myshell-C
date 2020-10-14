#include "headers.h"
#include "prompt.h"
int user_name()
{
	struct utsname s;
	char host_name[400];

	if(getlogin_r(host_name,400)==-1)
	{
		// handle error
		return -1;
	}
	
	if((uname(&s))==-1)
	{
		// handle error
		return -1; 
	}
	else
	{
		printf("%s@%s:",host_name,s.nodename);
		char *path;
		path = (char *)malloc(1000);
		if(getcwd(path , 1000)==NULL)
		{
			// handle error
			return -1;
		}
		else
		{
			ll check=0;
			ll k1=strlen(path),k2=strlen(shell_path);
			for(ll i=0;i<k1 && i<k2;i++)
			{
				if(shell_path[i]!=path[i])
				{
					check=-1;
					break;
				}
			}
			if(check==-1 || k1<k2)
				printf("%s : ",path);
			else
			{
				printf("~");
				for(ll i=k2;i<k1;i++)
					printf("%c",path[i]);
				printf(" : ");
			}
		}
	}
	
	return 0;
}
