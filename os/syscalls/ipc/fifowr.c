/* 	program to demonstrate ipc using named pipe:
 		- writer process
 ------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

//writer process
int main(void)
{
	int fw;
	//open a pipe file for writing 
	fw = open("dac_fifo", O_WRONLY);
	if(fw < 0)
	{
		perror("open failed...");
		_exit(1);
	}
	//write contents into the file
	write(fw, "SunBeam", 7);
	//close a file
	close(fw);
	return 0;
}
