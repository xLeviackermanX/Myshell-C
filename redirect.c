#include "headers.h"



int redirect(int in, int  out , int append, char *i_file,char *o_file , char *str , int z)
{
	//printf("%s \n%s \n%s\n",str,i_file,o_fi);
	int f[2];
	f[0]=0;f[1]=1;
	//printf("%d\n", append);
	if(in==1)
	{
		char *file = strtok(i_file," ");
		f[0]=open(file,O_RDONLY);
		if(f[0]==-1)
		{
			perror("");
			return -1;
		}
	}
	else if(in==0)
		f[0]=z;
	if(out==1)
	{
		char *file=strtok(o_file," ");
		//printf("%s\n",file );
		if(append==1)
			 f[1]=open(file,O_RDWR| O_APPEND | O_CREAT , 0644);
		else
			 f[1]=open(file,O_RDWR| O_CREAT, 0644);

		if(f[1]==-1)
		{
		
			perror("");
			return 1;
		}
	
	}
	else if(out==0)
		f[1]=z;
	//printf("%d %d\n",out,f[1] );
	
	parse_command(f[0],f[1],str);
	
	return 1;

}
int if_red(int in, int out , char *s)
{

	char str[1000];
	strcpy(str,s);
	int ch[100]={0};
	ll k=strlen(str);
	int j=0;
	for(ll i=0;i<k;i++)
	{
		if(str[i]=='>')
		{
			ch[j]=1;
			str[i]='-';
			if(i+1<k && str[i+1]=='>')
			{
				str[i+1]='-';
				ch[j]=2;
				i++;
			}
			
			j++;
		}
		else if(str[i]=='<')
		{
			str[i]='-';
			ch[j]=-1;
			j++;
		}
		
	}
	
	if(ch[0]==0)
		return 0;
	else if(ch[3]!=0)
	{
		printf("This level of redirection functionality is not allowed in the shell\n");
		return -1;
	}
	else if(ch[0]!=0 && ch[1]==-1)
	{
		printf("This sequence of redirection is not allowed\n");
		return -1;
	}
	else if(ch[0]==-1 && ch[1]!=0)
	{
		int append=0;
		if(ch[1]==2)
			append=1;
		char  *com = strtok(str,"-");
		char  *i_file = strtok(NULL,"-");
		char *o_file = strtok(NULL,"-");
		int re=redirect(1,1,append , i_file ,o_file , com,0);
		return re;
	}
	else if(ch[0]==-1)
	{

		char *com = strtok(str,"-");
		char *i_file=strtok(NULL,"-");
		int re = redirect(1,0,0,i_file,"",com,out);
		return re;
	}
	else if(ch[0]!=0)
	{
		int append=0;
		if(ch[0]==2)
			append=1;
		char *com=strtok(str,"-");
		char *o_file=strtok(NULL,"-");
		int re=redirect(0,1,append,"",o_file,com,in);
		return re;
	}
	else
	{
		return 0;
	}
	
}
/*int main()
{
	char i_file[]="hello.txt",o_file[]="" , str[]="echo yoman5525";
	redirect(0,1,0,i_file,o_file,str);
	return 0;
}*/