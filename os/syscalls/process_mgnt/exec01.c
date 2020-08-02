#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(void)
{
	int ret;
	int status;

	printf("parent is started !!!\n");
	ret = fork();
	if( ret == -1 )
	{
		perror("fork() failed !!!\n");
		_exit(1);
	}


	if( ret == 0 )//child process
	{
		//int err = execl("cmdline.out", "./cmdline.out", "sachin", "sourav", "rahul", NULL);
		//int err = execl("/bin/ls", "ls", "-l", "-i", "/home/sunbeam", NULL);
		int err = execlp("ls", "ls", "-l", "-i", "/home/sunbeam", NULL);
		if( err == -1 )
		{
			perror("exec() failed !!!\n");
			_exit(1);
		}
	}
	else//parent process
	{
		//parent process may contains logic of its own

		wait(&status);
		printf("parent is terminated !!!\n");
	}

	return 0;
}
