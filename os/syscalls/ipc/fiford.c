/* 	program to demonstrate ipc using named pipe:
 		- reader process
 ------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//reader process
int main(void)
{
	int fr;
	char str[20];

	//open a pipe file in read only mode
	fr = open("dac_fifo", O_RDONLY);
	if(fr < 0)
	{
		perror("open failed ...\n");
		_exit(1);
	}

	//read contents from a file
	read(fr, str, sizeof(str));
	printf("read : %s\n", str);

	//close a file
	close(fr);
	return 0;
}
