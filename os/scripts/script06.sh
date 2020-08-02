#!/bin/bash

clear
echo -n "enter filepath: "
read filepath

if [ -e $filepath ]
then
	if [ -f $filepath ]
	then
		echo "contents of reg file are: "
		cat $filepath
	elif [ -d $filepath ]
	then
		echo "contents of dir file are: "
		ls $filepath
	else
		echo "$filepath is neither reg file nor dir file"
	fi
else
	echo "invalid filepath"
fi
