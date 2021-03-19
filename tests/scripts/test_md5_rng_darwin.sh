#! /bin/bash

if (( $#!=3 ))
then
	echo -e "Usage:\n$0 <rounds> <ft_ssl> <rng_file_size>"
	exit 1
fi

CNT=$1
FTSSL=$2
blim=$3
tmp=md5rngtest
orig=md5originaltest
res=md5ftssltest

C_GREEN="\033[32m"
C_RED="\033[31m"
C_EOC="\033[0m"

function print_status_bar() {
    echo -ne "[ $1 / $2 ] $3"
}

RANDOM=$(date +%N)

rt=0
ot=0
fst=0
rng_bytes=0

SCRIPT_START=$(date +"%s.%N")
for i in `seq $CNT`
do
	r=$(( ($RANDOM % $blim) + 1 ))
	head -c $r </dev/urandom > $tmp
	md5 -q $tmp > $orig
	./$FTSSL md5 $tmp > $res
	d=$(diff -q $orig $res)
	if [ "$d" != "" ]
	then
		echo -e "\n${C_RED}ERROR${C_EOC}"
		exit 1
	fi
    print_status_bar $i $CNT "\r"
done
print_status_bar $i $CNT "\n"
echo -e "${C_GREEN}Success${C_EOC}"
rm $tmp $orig $res