/*
filename: main.c
-------------------------------------------------------*/

#include<stdio.h>
#include<unistd.h>

#include"functions.h"

int main(void)
{
	emp_t e1;
	int id;

	while(1)
	{
		int choice = menu();
		switch(choice)
		{
			case EXIT: _exit(0);
			case ACCEPT_RECORD:
				accept_employee_record(&e1);
				break;
			case DISPLAY_RECORD:
				printf("%-10s %-20s %-10s\n", "empid", "name", "salary");
				display_employee_record(&e1);
				break;
			case WRITE_RECORD:
				write_record_into_file(&e1);
				break;
			case READ_RECORDS:
				read_records_from_file();
				break;
			case UPDATE_RECORD:
				printf("enter an empid of an employee which is to update: ");
				scanf("%d", &id);
				if( update_record(id) )
					printf("record updated successfully...\n");
				else
					printf("record not found !!!\n");
				break;
			case DELETE_RECORD:
				printf("enter an empid of an employee which is to delete: ");
				scanf("%d", &id);
				delete_record(id);
				break;
		}
	}

	return 0;
}
