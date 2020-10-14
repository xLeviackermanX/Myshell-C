#include "headers.h"
#include "inbuilt.h"
int echo(int in ,int out , char *str)
{
	//printf("%s\n",str );
	char *ch;
	ch= strtok(str," ");
	while(ch!=NULL)
	{
		ch=strtok(NULL," ");
		if(ch!=NULL)
		{
			//printf("%s\n",ch);
			int y = write(out,ch,strlen(ch));
			y=write(out," ",1);
			//printf("%d\n",y );

		}	
		
	}
	write(out ,"\n\0", sizeof("\n\0"));
	return 0;
}

