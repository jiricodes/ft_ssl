#! /bin/bash

if (( $#<1 ))
then
	echo -e "Usage:\n$0 <forbidden_list> [directories]"
	exit 1
fi

fb=$1
ret=0
declare -i i=0

C_GREEN="\033[32m"
C_RED="\033[31m"
C_EOC="\033[0m"

check_details()
{
	d=$1
	for f in $d/*
	do
		c=$(cat $f | grep -f $fb -c)
		if (( $c!=0 ))
		then
			echo -e "\t$f:"
			while read p
			do
				r=$(cat $f | grep -n $p)
				if [[ ! -z $r ]]
				then
					echo -ne "\t\t"
					echo "$r"
				fi
			done < $fb
		fi
	done
}

# SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

# fb=$SCRIPTPATH"/forbidden_list"

for a in "$@"
do
	if (( $i != 0 ))
	then
		c=$(cat $a/* | grep -f $fb -c)
		if [ "$c" -ne 0 ]
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