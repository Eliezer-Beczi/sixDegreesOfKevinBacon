#!/bin/bash

# wget -qO- https://www.rottentomatoes.com/m/flatliners | cat | grep -e "<span title=".*">" | cut -d "\"" -f 2 | sed 's/\ /\-/g'

numOfMovies=`wc -l < filmek.txt`
aux="https://www.rottentomatoes.com/m/"

echo "$numOfMovies" > graf.txt

while read line
do
	url="$aux$line"
	data=`wget -qO- $url | cat`
	cast=`grep -e "<span title=".*">" <<< $data | cut -d "\"" -f 2 | sed 's/\ /\-/g'`
	titleName=`grep -e "\"titleName\": \".*\"" <<< $data | cut -d "\"" -f 4 | sed 's/\ /\-/g'`

	echo >> graf.txt
	echo -n "$titleName : " >> graf.txt

	for actor in $cast
	do
		echo -n "$actor " >> graf.txt
	done

	echo >> graf.txt
done < filmek.txt
