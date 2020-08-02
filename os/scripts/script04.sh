#!/bin/bash

# script to calculate area of circle 

clear
PI=3.14

echo -n "enter radius: "
read rad

area=`echo "$PI * $rad * $rad" | bc`
echo "area = $area"

exit

