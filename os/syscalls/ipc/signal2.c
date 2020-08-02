#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//step1: implement signal handler function
void sigint_handler(int sig)
{
	printf("SIGINT :: signal caught: %d\n", sig);
}

void sigterm_handler(int sig)
{
	printf("SIGTERM :: signal caught: %d\n", sig);
}

//cannot be handled
void sigkill_handler(int sig)
{
	printf("SIGKILL :: signal caught: %d\n", sig);
}

int main()
{
	int i=0;
	//step2: register signal handler with os
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigterm_handler);
	signal(SIGKILL, sigkill_handler);

	while(1)
	{
		printf("running : %d\n", ++i);
		sleep(1);
	}
	return 0;
}

