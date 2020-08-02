/*
filename: functions.c
this file contains of definitions of functions 
-------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int menu(void)
{
	int choice;

	printf("0. exit\n");
	printf("1. accept record\n");
	printf("2. display record\n");
	printf("3. write record into a file\n");
	printf("4. read all records from a file\n");
	printf("5. update record\n");
	printf("6. delete record\n");
	printf("enter the choice: ");
	scanf("%d", &choice);
	
	return choice;
}

void write_record_into_file(emp_t *pe)
{
	//open a file or to a create a new file
	int fd = open("empdb.db", O_CREAT|O_RDWR|O_APPEND, 0644);
	if( fd == -1 )
	{
		perror("open() failed !!!\n");
		_exit(1);
	}

	//write a record into the file
	write(fd, pe, sizeof(emp_t));

	//close a file
	close(fd);
}

void read_records_from_file(void)
{
	emp_t e;
	//open a file
	int fd = open("empdb.db", O_RDONLY);
	if( fd == -1 )
	{
		perror("open() failed !!!\n");
		_exit(1);
	}

	//read all records from the file one by one and display
	while( read(fd, &e,sizeof(emp_t)) > 0 )
	{
		display_employee_record(&e);
	}

	//close a file
	close(fd);
}

int update_record(int id)
{
	emp_t e;
	long int offset = sizeof(emp_t);
	int update = 0;

	//open a file for read as well write purpose
	int fd = open("empdb.db", O_RDWR);
	if( fd == -1)
	{
		perror("open() failed !!!\n");
		_exit(1);
	}

	//search record to be updated - read records
	while( read(fd, &e, sizeof(emp_t)) > 0 )
	{
		//if record is found then update it
		if( e.empid == id )
		{
			display_employee_record(&e);
			accept_employee_record(&e);
			//reposition file offeset
			lseek(fd,-offset,SEEK_CUR);
			//overwrite updated record into a file
			write(fd,&e,sizeof(emp_t));
			update = 1;
			break;
		}
	}

	//close a file
	close(fd);
	return update;
}

void delete_record(int id)
{
	emp_t e;

	//open two files - src & dest: open src file for read only purpose
	//& create new dest file
	int fs = open("empdb.db", O_RDONLY);
	int fd = open("temp.db", O_CREAT| O_WRONLY, 0644);
	if( fs == -1 || fd == -1 )
	{
		perror("open() failed !!!\n");
		_exit(1);
	}

	//read records from src file one by one
	while( read(fs, &e, sizeof(emp_t)) > 0 )
	{
		//write all the records into the temp file except record to be deleted
		if( e.empid != id )
		{
			write(fd, &e, sizeof(emp_t));
		}
	}

	//close both the files
	close(fs);
	close(fd);

	//delete original file
	unlink("empdb.db");
	//rename temp filename by original filename
	rename("temp.db", "empdb.db");	
}


















