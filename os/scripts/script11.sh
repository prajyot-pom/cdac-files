#!/bin/bash

function addition( )
{
	sum=`expr $1 + $2`
	echo "$sum"
}

clear

echo -n "enter n1 : "
read n1

echo -n "enter n2 : "
read n2

#function call - syntax1
# addition $n1 $n2

#function call - syntax2
sum=$(addition $n1 $n2)
echo "sum = $sum"

exit

