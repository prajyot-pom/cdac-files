#include<stdio.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
	if( argc != 3 )
	{
		printf("invalid no. of args !!!\n");
		_exit(1);
	}


	if( ( link(argv[1], argv[2]) ) != -1 )
		printf("hard link got created successfully...\n");

	return 0;
}
