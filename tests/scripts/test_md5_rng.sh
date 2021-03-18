#! /bin/bash
N=$1
FTSSL=$2
tmp=md5rngtest
orig=md5originaltest
res=md5ftssltest

function timediff() {
    TIME_DIFF=$(printf %.6f $(echo "scale=6;$2 - $1" | bc))
}

function avgtime() {
    TIME_AVG=$(printf %.6f $(echo "scale=6;$1 / $2" | bc))
}

# params - random_gen, original md5sum, ft_ssl, cnt
function averages()
{
    avgtime $1 $4
    A_RNG=$TIME_AVG
    avgtime $2 $4
    A_ORIG=$TIME_AVG
    avgtime $3 $4
    A_FTSSL=$TIME_AVG
}

function print_status_bar() {
    EST=$(echo "scale=4;($1 / $2) * ($3 - $2)" | bc)
    EST_FMT=$(date -u -d @0${EST} +"%T")
    echo -ne "[ $2 / $3 || ETF $EST_FMT || AVG_RNG $A_RNG || AVG_MD5sum $A_ORIG || AVG_FTSSL $A_FTSSL ] $4"
}

rt=0
ot=0
fst=0

SCRIPT_START=$(date +"%s.%N")
for i in `seq $N`
do
	START=$(date +"%s.%N")
	r=$(( ($RANDOM % 4096) + 1 ))
	dd if=/dev/random of=$tmp bs=$r count=1 > /dev/null 2>/dev/null
	END=$(date +"%s.%N")
	timediff $START $END
	rt=$(echo "scale=6;$rt + $TIME_DIFF" | bc)
	START=$(date +"%s.%N")
	md5sum $tmp | awk '{print $1}' > $orig
	END=$(date +"%s.%N")
	timediff $START $END
	ot=$(echo "scale=6;$ot + $TIME_DIFF" | bc)
	START=$(date +"%s.%N")
	./$FTSSL md5 $tmp > $res
	END=$(date +"%s.%N")
	timediff $START $END
	fst=$(echo "scale=6;$fst + $TIME_DIFF" | bc)
	d=$(diff -q $orig $res)
	if [ "$d" != "" ]
	then
		echo -e "\nERROR"
		exit 1
	fi
	CURRENT=$(date +"%s.%N")
    timediff $SCRIPT_START $CURRENT
	averages $rt $ot $fst $i
    print_status_bar $TIME_DIFF $i $N "\r"
done
print_status_bar $TIME_DIFF $i $N "\n"
prc=$(echo "scale=6; ($A_FTSSL / $A_ORIG) * 100" | bc)
printf "FT_SSL relative speed %.2f" $prc
rm $tmp $orig $res