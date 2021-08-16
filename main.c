 #include "headers.h"
#include "inbuilt.h"
#include "prompt.h"
#include "parse.h"

int main()
{
	cur_pid=-1;
	x=0;
	
	
	if(getcwd(shell_path,1000)==NULL)
	{
		//error handle
	}
	shell_pid=getpid();
	memset(bg,-1,sizeof(bg));
	while(1)
	{
		for(ll i=0;i<1000;i++)
		{
			if(bg[i]==-1)
					continue;
			int b;
			int f = waitpid(bg[i],&b ,WNOHANG);

			if(f==-1){
				//error handling.
				continue;
			}

			if(f!=0)
			{
				if(WIFEXITED(b))
					fprintf(stderr, "%s with pid %d exited normally\n",pro[i],bg[i]);
				else
					fprintf(stderr , "%s with pid %d exited abnormally\n",pro[i],bg[i]);
				bg[i]=-1;
				for(ll j=i+1;j<1000;j++)
					bg[j-1]=bg[j];
				i--;
			}
		}
		
		user_name();
		char *command;
		long unsigned int size=10000;
		command = (char *)malloc(size);

		getline(&command,&size, stdin);


		if(feof(stdin) || strcmp(command,"quit\n")==0)
		{
			printf("\n");
			exit(2);
		}
		ll k=strlen(command);
		command[k-1]='\0';
		
		//printf("%s\n", command);
		char *str=strtok(command,";");
		ll i=0;
		char arr[1000][1000];
		while(str!=NULL)
		{
			//printf("%s\n", str);
			strcpy(arr[i],str);
			i++;
			str=strtok(NULL,";");
		}
		for(ll j=0;j<i;j++)
		{
			//printf("%s\n",arr[j] );
			parse_command(0,1,arr[j]);	
		}
		//printf("what's happening here\n");
		//printf("\n");
	}
	return 0;

}