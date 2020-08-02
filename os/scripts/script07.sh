#!/bin/bash

# script to print a table of a given number

clear

echo -n "enter the num: "
read num

echo "while: table of a $num is: "
i=1
while [ $i -le 10 ]
do
	res=`expr $num \* $i`
	echo "$res"
	i=`expr $i + 1`
done

echo "until: table of a $num is: "
i=1
until [ $i -gt 10 ]
do
	res=`expr $num \* $i`
	echo "$res"
	i=`expr $i + 1`
done

echo "for: table of a $num is: "
for i in 1 2 3 4 5 6 7 8 9 10
do
	res=`expr $num \* $i`
	echo "$res"
done

exit











