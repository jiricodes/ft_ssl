#! /bin/bash

while  read p; do
	echo -ne "unittest_hexstr_one_str(\"$p\", \""
	b=$(echo -n "$p" | xxd -c 1 | awk '{ print $2 }' | awk 'BEGIN{ORS=""}1' | sed 's/ *$//g')
	b=${b%$'\n'} 
	echo -e "$b\", &current, total);"
done < $1