#!/bin/bash

sum=0

for params in $*
do
	sum=`expr $sum + $params`
done

echo "sum = $sum"

exit


