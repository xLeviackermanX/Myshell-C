#include "headers.h"
#include "inbuilt.h"
#define ll long long int 
// char shell_path[]="/home/priyansh/shell";
int cd(char *str)
{
	char *path;
	ll k1=strlen(str);
	path = (char *)malloc(1000);
	if(str[0]=='~')
	{
		path = strcpy(path,shell_path);
		ll k2=strlen(path);
		for(ll i=1;i<k1;i++)
			path[k2-1+i]=str[i];
		path[k2+k1-1]='\0';
	}
	else
	{
		path = strcpy(path,str);
	}
	int x=chdir(path);
	if(x==-1)
	{
		//handle error
		perror(" : ");
	}

	return 0;
}
