# Myshell-C
#COMMAND THAT I IMPLEMENTED:-

1. cd command with your code directory being home directory for shell
2. echo, pwd , ls (with flags l and a)
3. pipeline
4. redirection
5. pinfo <pid> (finds info about a process with given pid)
6. jobs
7. kjob (send signals to a process)
8. fg
9. bg
10. overkill (kill our background process)
11. valid command which runs in your bash terminal also with option of running in foreground or background if used with "&"
12. Signal handlers like shell will exit on ctrl+d , process can be stopped using ctrl+c and foreground 	process will get into sleep mode on using ctrl+z. 


1. Shell loop is in main.c
2. Shell path is stored in a global variable before starting the shell loop
3. Shell is printing username and hostname in prompt.c
4. After prompting shell takes an user command as input
5. Command is parsed in parse.c , here we decide that which function to call by identifying appropriate command
6. Functionality of ls , cd and echo command is written in ls.c , cd.c and echo.c respectively
7. Functionality of executing a foreground and backgorund process is stored in foregorund.c and background.c respectively
8. Functionality of pinfo is stored in pinfo.c
9. MAKEFILE IS MADE FOR COMPILING ALL THE CODES WHICH IS STORED IN DIRECTORY OF SHELL CODES. 
   SO TO COMPILE CODE JUST GO TO THE WORKING DIRECTORY OF SHELL CODES AND WRITE MAKE COMMAND IN THE TERMINAL.
