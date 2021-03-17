#! /bin/bash

while  read p; do
	echo -ne "unittest_md5_one(\"$p\", \""
	b=$(echo -n $p | md5sum | awk '{print $1}')
	b=${b%$'\n'} 
	echo -e "$b\", &current, total);"
done < $1