#include "headers.h"  
#include "inbuilt.h"
#include<pwd.h>
#include<grp.h>
int ls(int in , int out , char *str)  
{ 
    //char shell_path[1000]="";
    //strcpy(shell_path,"/home/priyansh/shell");
    //char home_path[1000]="";
    //strcpy(home_path,"/home/priyansh");
   
    int l_f=0,a_f=0,v_f=1;
    char *com=strtok(str," ");
    char  argv[1000][1000];
    ll argc=0;
    while(com!=NULL)
    {
        com=strtok(NULL," ");
        if(com!=NULL)
        {
            if(com[0]=='-')
            {
                ll k=strlen(com);
                for(ll i=1;i<k;i++)
                {
                    if(com[i]=='a')
                        a_f=1;
                    else if(com[i]=='l')
                        l_f=1;
                    else if( com[i]!=' ' && com[i]!='\n' && com[i]!='\n')
                        v_f=0;
                }
            }
            else
            {
                strcpy(argv[argc],com);
                argc++;
            }
        }
    }
    if(v_f==0)
    {
        printf("A wrong flag is used \n");
        return -1;
    }
    struct stat s,t;

    if(argc==0)
    {
        argc++;
        strcpy(argv[0],".");
    }
    char check[1024];
    for(ll optind=0; optind < argc; optind++){      
        char path[1000]="";
        if(argv[optind][0]=='~')
        {
            strcpy(path,shell_path);
            sprintf(check ,"%s\n",path );
            write(out , check , strlen(check));
            ll k2=strlen(path);
            ll i;
            for( i=1;argv[optind][i]!='\0';i++)
                path[k2-1+i]=argv[optind][i];
            path[i+k2-1]='\0';
        }
        else
            strcpy(path,argv[optind]);
        if(stat(path,&s)==0)
        {
            if(S_ISDIR(s.st_mode))
            {
                
                sprintf(check,"%ld\n%s :\n",s.st_size,argv[optind]);
                write(out,check,strlen(check));
                DIR *d=opendir(path);
                if(d==NULL)
                {   
                    perror("");
                }
                struct dirent *de;
                while((de=readdir(d))!=NULL)
                {  
                    char ch[1000]="";
                    strcpy(ch,path);
                    strcat(ch,"/");
                    strcat(ch,de->d_name);
                    if(stat(ch,&t)==0)
                    {  
                        if((*(de->d_name)!='.' && a_f==0) || (a_f==1))
                        {

                            if(l_f==1)
                            {
                                if(S_ISDIR(t.st_mode))
                                    write(out,"d",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IRUSR)
                                    write(out,"r",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IWUSR)
                                    write(out,"w",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IXUSR)
                                    write(out,"x",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IRGRP)
                                    write(out,"r",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IWGRP)
                                    write(out,"w",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IXGRP)
                                    write(out,"x",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IROTH)
                                    write(out,"r",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IWOTH)
                                    write(out,"w",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IXOTH)
                                    write(out,"x  ",sizeof("x  "));
                                else
                                    write(out,"-  ",sizeof("-  "));
                                sprintf(check,"%ld  %s  %s",t.st_nlink,getpwuid(t.st_uid)->pw_name,getgrgid(t.st_gid)->gr_name);
                                write(out,check,strlen(check));
                                sprintf(check,"%ld  ",t.st_size);
                                 write(out,check,strlen(check));
                                struct tm dt;
                                dt = *(gmtime(&t.st_ctime));
                                sprintf(check ," %d-%d-%d  ", dt.tm_mday, dt.tm_mon, dt.tm_year + 2000);
                                 write(out,check,strlen(check));
                            }
                            sprintf(check ,"%s  \n",de->d_name);
                             write(out,check,strlen(check));
                        }
                    }
                }
                closedir(d);
            }
            else
            {
                if(l_f==1)
                {

                    write(out,"-",1);

                     if(S_ISDIR(t.st_mode))
                                    write(out,"d",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IRUSR)
                                    write(out,"r",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IWUSR)
                                    write(out,"w",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IXUSR)
                                    write(out,"x",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IRGRP)
                                    write(out,"r",1);
                                else
                                     write(out,"-",1);

                                if(t.st_mode & S_IWGRP)
                                    write(out,"w",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IXGRP)
                                    write(out,"x",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IROTH)
                                    write(out,"r",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IWOTH)
                                    write(out,"w",1);
                                else
                                    write(out,"-",1);

                                if(t.st_mode & S_IXOTH)
                                    write(out,"x  ",sizeof("x  "));
                                else
                                    write(out,"-  ",sizeof("-  "));
                    sprintf(check , "%ld  ",s.st_size);
                     write(out,check,strlen(check));
                    sprintf(check,"%ld  %s  %s",t.st_nlink,getpwuid(t.st_uid)->pw_name,getgrgid(t.st_gid)->gr_name);
                     write(out,check,strlen(check));
                    struct tm dt;
                    dt = *(gmtime(&s.st_ctime));
                    sprintf(check," %d-%d-%d  ", dt.tm_mday, dt.tm_mon, dt.tm_year + 2000);
                     write(out,check,strlen(check));
                }
                sprintf(check ,"%s\n",path);
            }

        }
        else
        {
        	perror("");
        	return -1;
        }


    }

    return 0;  
} 


