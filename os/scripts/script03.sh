#!/bin/bash

# script to calculate area of rectangle

clear

echo -n "enter lenght: "
read len

echo -n "enter breadth: "
read br

area=`expr $len \* $br`
echo "area = $area"

exit

