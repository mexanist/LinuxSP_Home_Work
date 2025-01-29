#!/bin/bash
i=1

for i in {1..20};
	do
		[ -d "./$i" ] || mkdir ./$i
		[ -e "./$i/i.txt" ] || touch ./$i/$i.txt
		[ -L "~/$i.txt" ] || ln -s ~/$i/$i.txt  ~/$i.txt
		echo "$i.txt" > ./$i/$i.txt
	done
for i in {1..20};
	do
		if [ $i != 4 ] && [ $i != 14 ]; then
			rm $i/$i.txt
		fi
	done
echo "test" > 4/4.txt
 

