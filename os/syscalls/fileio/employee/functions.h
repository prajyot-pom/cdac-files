/*
filename: functions.h
this file contains of declarations of functions 
-------------------------------------------------------*/
#ifndef __FUN_H
#define __FUN_H

#include"emp.h"

enum menu_options{ EXIT, ACCEPT_RECORD, DISPLAY_RECORD, WRITE_RECORD,
READ_RECORDS, UPDATE_RECORD, DELETE_RECORD };

int menu(void);
void write_record_into_file(emp_t *pe);
void read_records_from_file(void);
int update_record(int id);
void delete_record(int id);


#endif

