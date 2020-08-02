#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>


int main(int argc, char *argv[])
{

	DIR *dir = NULL;
	struct dirent *dirent = NULL;

	if( argc != 2 )
	{
		printf("invalid no. of args !!!\n");
		_exit(1);
	}

	//open a dir file
	dir = opendir(argv[1]);
	if( dir == NULL )
	{
		perror("opendir() failed !!!\n");
		_exit(1);
	}

	//read dir file contents
	printf("dir contents are: \n");
	while( ( dirent = readdir(dir) ) != NULL )
	{
		printf("%lu \t%s\n", dirent->d_ino, dirent->d_name);
	}
	
	//close dir file
	closedir(dir);

	return 0;
}
