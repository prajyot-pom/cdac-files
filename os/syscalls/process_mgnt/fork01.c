/* fork01.c: demo of fork() syscall */
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void)
{
	printf("main() started !!!\n");

	fork();

	fork();

	fork();

	printf("main() exited !!!\n");

	return 0;
}
