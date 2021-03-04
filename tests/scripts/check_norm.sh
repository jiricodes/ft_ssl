#! /bin/bash

if (( $#<1 ))
then
	echo -e "Usage:\n$0 <norminette command> [directories]"
	exit 1
fi

C_GREEN="\033[32m"
C_RED="\033[31m"
C_EOC="\033[0m"

check_details()
{
	d=$1
	for f in $d/*
	do
		c=$($norm $f | grep -c Error)
		if (( $c!= 0))
		then
			bn=$(basename $f)
			echo -e "\t$bn: $c"
		fi
	done
}

declare -i ret=0
declare -i i=0
norm=$1

for a in "$@"
do
	if (( $i!=0 ))
	then
		c=$($norm $a | grep -c Error)
		if (( $c!= 0))
		then
			echo -e "$a: ${C_RED}Fail$C_EOC"
			check_details $a
			ret=1
		else
			echo -e "$a: ${C_GREEN}Clean$C_EOC"
		fi
	else
		i=1
	fi
done
exit $ret