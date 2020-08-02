/* demo of pipe() syscall using parent and child process */

#include <stdio.h>
#include <unistd.h>

#define RD 0
#define WR 1

int main(void)
{
	int ret, arr[2];
	char str[20], buf[20];

	pipe(arr);

	ret = fork();
	if(ret == 0)
	{	
		//child: writer
		//close the read end
		close(arr[0]);
		printf("child: enter string : ");
		gets(buf);
		//write data into a buffer created by pipe()
		write(arr[1], buf, sizeof(buf));
		//close write end
		close(arr[1]);
	}
	else
	{	
		//parent: reader
		//close write end of a kernel buffer
		close(arr[1]);

		//read data from kernel buffer created by pipe()
		read(arr[0], str, sizeof(str));
		//display contents read from kernel buffer
		printf("parent: read from pipe: %s\n", str);

		//close read end
		close(arr[0]);
	}
	return 0;
}



