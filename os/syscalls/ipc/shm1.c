/* shared memory model - by using global variable */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct shm
{
	int cnt;
}shm_t;

//global variable
shm_t var;

int main(void)
{
	shm_t *ptr = NULL;
	int ret, i, status;
	ptr = &var;
	ptr->cnt = 0;

	ret = fork();

	if(ret == 0)
	{
		//child process --> increment
		for(i=0; i<10; i++)
		{
			ptr->cnt++;
			printf("child : %d\n", ptr->cnt);
			sleep(1);
		}
	}
	else
	{
		//parent process --> decrement
		for(i=0; i<10; i++)
		{
			ptr->cnt--;
			printf("parent : %d\n", ptr->cnt);
			sleep(1);
		}

		//-> to avoid zombie state of child process
		wait(&status);

		printf("final count = %d\n", ptr->cnt);
	}

	return 0;
}
