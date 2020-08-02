#!/bin/bash

# script to check entered year is a leap year or not

clear

echo -n "enter the year: "
read yr

if [ `expr $yr % 4` -eq 0 -a `expr $yr % 100` -ne 0 -o `expr $yr % 400` -eq 0 ]
then
	echo "$yr is a leap year"
else
	echo "$yr is not a leap year"
fi

exit

