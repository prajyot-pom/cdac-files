#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//implement signal handler for SIGCHLD
void sigchld_handler(int sig)
{
	int status;
	wait(&status);
	printf("child exit value : %d\n", WEXITSTATUS(status));
}

int main()
{
	int ret;
	int i;
	//register signal handler entry with an OS
	signal(SIGCHLD, sigchld_handler);

	ret = fork();
	if(ret == 0)
	{
		for(i=0; i<20; i++)
		{
			printf("child: %d\n", i);
			sleep(1);
		}
		_exit(6);
	}
	else
	{
		for(i=0; i<40; i++)
		{
			printf("parent: %d\n", i);
			sleep(1);
		}
	}
	return 0;
}

