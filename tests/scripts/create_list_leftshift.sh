#! /bin/bash

LEN=$1
RANDOM=$(date +%N)

TMP=tmp_leftshiftgen

rm -f $TMP
for i in `seq $LEN`
do
	for a in `seq 4`
	do
		for b in `seq 8`
		do
			r=$(( $RANDOM%2 )) >> $TMP
			echo -n "$r" >> $TMP
		done
		# echo -n " " >> $TMP
	done
	echo "" >> $TMP
done
while read p
do
	r=$(( $RANDOM%32 ))
	f=${p:0:$r}
	b=${p:$r}
	echo "unittest_leftshift_one(0b$p, $r, 0b$b$f, &current, total);"
done < $TMP