#!/bin/bash 
chmod +x ./course_stat.sh

#checking if the number of arguments is correct, if not exit
if [ "$#" -ne 1 ]; then
	echo "Usage: $0 DIRECTORY" >&2
	echo "Wrong number of arguments"
	exit 1
fi 

#checking if there is a file from the correct format
x=$(ls $1.txt) 
if [[ -z $x ]];then
	echo "course not found"
	exit 1
fi

#searching and deleting if there is already a directory
echo $1
y=$(find $1_stat)
if [[ ! -z $y ]];then
	rm -dr $y
fi

#creating a new empty directory
mkdir "$1"_stat 

#reading the grades to a new file
awk '{print $2}' $1.txt > ./"$1"_stat/grades.txt

#compile and run calc_statistics.c
gcc -c -g -Wall calc_statistics.c
gcc -o calc_statistics.exe calc_statistics.o
./calc_statistics.exe

#printing to the screen 
cat "course_statistics.txt"
