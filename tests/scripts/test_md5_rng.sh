#! /bin/bash
N=$1
FTSSL=$2
tmp=md5rngtest
for i in `seq $N`
do
	dd if=/dev/random of=$tmp bs=124 count=1 > /dev/null 2>/dev/null
	p=$(cat $tmp) > /dev/null 2>/dev/null
	echo -n $p | md5sum | awk '{print $1}'
	./$FTSSL md5 "$p"
done