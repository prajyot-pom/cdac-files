/* demo -- pipe() syscall using single process */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret, arr[2];
	char str[20];

	ret = pipe(arr);

	if(ret < 0)
	{
		perror("pipe() failed.");
		_exit(1);
	}

	//after creating kernel buffer successfully
	//write data into buffer from write end -> whose fd is in arr[1]
	write(arr[1], "dac pune",14);

	//read data from buffer from read end --> whose fd is in arr[0]
	read(arr[0], str, sizeof(str));

	printf("read: %s\n", str);

	//close the write end buffer
	close(arr[1]);

	//close read end of the buffer
	close(arr[0]);

	return 0;
}

/*
	 + pipe() system call: create a pipe
	 function prototype: int pipe(int pipefd[2]);
	 function call: int ret = pipe(arr);//where as arr is an array of size 2
	 - pipe() creates a pipe, a unidirectional data channel that can be used for inter‐
	 process communication.
	 - the array pipefd is used to return two file descriptors referring to the ends
	 of the pipe.
	 - pipefd[0] refers to the read end of the pipe.
	 - pipefd[1] refers to the write end of the pipe.
	 - data written to the write end of the pipe is buffered by the kernel until it
	 is read from the read end of the pipe.
	 - return value: int
	 on success 0 is returned
	 on error -1 is returned
-----------------------------------------------------------------------------*/


