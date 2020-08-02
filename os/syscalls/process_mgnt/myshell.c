#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(void)
{
	char cmd[256];
	char *cptr = NULL;
	char *args[32];
	int i=0;

	while(1)
	{
		i=0;
		//step1: accept command from the user in string format
		printf("cmd>");
		gets(cmd);

		//step2: extract all its tokens and store them into an array of char *
		cptr = strtok(cmd, " ");
		args[i] = cptr;
	
		do
		{
			i++;
			cptr = strtok(NULL, " ");
			args[i] = cptr;
		}while( cptr != NULL );

		//args[0] will be always name of the command
		//step3: if command is an internal command
		if( strcmp(args[0], "cd") == 0 )
			chdir(args[1]);
		else
		if( strcmp(args[0], "exit") == 0 )
			_exit(0);
		else//if command is an external command -> fork() + exec()
		{
			int status;

			int ret = fork();
			if( ret == -1 )
			{
				perror("fork() failed !!!\n");
				_exit(1);
			}

			if( ret == 0 )//child process
			{
				int err = execvp(args[0], args);
				if( err == -1 )
				{
					perror("exec() failed !!!\n");
					_exit(1);
				}
			}
			else//parent process
			{
				wait(&status);
			}
		}
	}//end of while loop

	return 0;
}

