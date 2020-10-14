#include "headers.h"
#include "foreground.h"

void sig_handler(int sig)
{
    if(cur_pid!=-1)
    {
        kill(cur_pid , SIGSTOP);
        x=1;
    }

}
int foreground(int in  , int out , char *str)
{
    strcpy(cur_com , str);
      int resi=dup(STDIN_FILENO),reso=dup(STDOUT_FILENO);
       
    ll f=fork();
    if(f==0)
    {
        ex(in,out);
        signal(SIGINT , SIG_DFL);
        signal(SIGTSTP , SIG_DFL);
        char *arg[1000];
        char *ch=strtok(str," ");

        arg[0]=ch;
      //  write(reso,arg[0],strlen(arg[0]));
        ll i=1;
        //printf("%s\n",arg[0] );
        while(ch!=NULL)
        {
            ch=strtok(NULL," ");
            arg[i]=ch;
            i++;
         //   printf("%s\n",arg[i-1] );
        }
        int kk=0;

        int y=execvp(arg[0],arg);
        if(y==-1)
        {
            perror("wrong command");
        }
        exit(2);
    }
    else
    {
        signal(SIGINT,SIG_IGN);
        signal(SIGTSTP , sig_handler);
        cur_pid=f;
        while(1)
        {
            int a;
            int b = waitpid(f,&a,WNOHANG);
           // printf("%d\n",b );
          
            if(b!=0 || b==-1)
                break;
            if(x==1)
            {
                for(ll i=0;i<1000;i++)
                {
                    if(bg[i]==-1)
                    {
                        bg[i]=cur_pid;
                        strcpy(pro[i],cur_com);
                        break;
                    }
                }
                x=0;
                break;
            }

        }
    
        cur_pid=-1;
        //printf("yoyo\n");
        return 0;
    }
}
