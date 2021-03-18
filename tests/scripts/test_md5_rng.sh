#! /bin/bash
N=$1
FTSSL=$2
tmp=md5rngtest
orig=md5originaltest
res=md5ftssltest
for i in `seq $N`
do
	r=$(( ($RANDOM % 4096) + 1 ))
	dd if=/dev/random of=$tmp bs=$r count=1 > /dev/null 2>/dev/null
	md5sum $tmp | awk '{print $1}' > $orig
	./$FTSSL md5 $tmp > $res
	d=$(diff -q $orig $res)
	if [ "$d" != "" ]
	then
		echo -e "\nERROR"
		exit 1
	fi
	echo -ne "\r$i / $N"
done
echo ""
rm $tmp $orig $res