#! /bin/bash

while  read p; do
	echo -ne "unittest_binstr_one_str(\"$p\", \""
	b=$(echo -n "$p" | xxd -b -c 1 | awk '{ print $2 }' | awk 'BEGIN{ORS=" "}1' | awk '{for(i=NF;i>=1;i--) printf "%s ", $i;print ""}' | sed 's/ *$//g')
	b=${b%$'\n'} 
	echo -e "$b\", &current, total);"
done < $1