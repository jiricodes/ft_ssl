#! /bin/bash

if (( $#!=3 ))
then
	echo -e "Usage:\n$0 <rounds> <ft_ssl> <rng_file_size>"
	exit 1
fi

N=$1
FTSSL=$2
blim=$3
tmp=md5rngtest
orig=md5originaltest
res=md5ftssltest

C_GREEN="\033[32m"
C_RED="\033[31m"
C_EOC="\033[0m"

function timediff() {
    TIME_DIFF=$(printf %.6f $(echo "scale=6;$2 - $1" | bc))
}

function avgtime() {
    TIME_AVG=$(printf %.6f $(echo "scale=6;$1 / $2" | bc))
}

# params - random_gen, original md5sum, ft_ssl, rng_bytes, cnt
function averages()
{
    avgtime $1 $5
    A_RNG=$TIME_AVG
    avgtime $2 $5
    A_ORIG=$TIME_AVG
    avgtime $3 $5
    A_FTSSL=$TIME_AVG
    A_RNGBYTE=$(( $4 / ($5+1) ))
}

function print_status_bar() {
    EST=$(echo "scale=4;($1 / $2) * ($3 - $2)" | bc)
    EST_FMT=$(date -u -d @0${EST} +"%T")
	ELAPSED=$(date -u -d @0$1 +"%T")
    echo -ne "[ TIME $ELAPSED || $2 / $3 || ETF $EST_FMT || AVG_RNG $A_RNG || AVG_MD5sum $A_ORIG || AVG_FTSSL $A_FTSSL ] $4"
}

RANDOM=$(date +%N)

rt=0
ot=0
fst=0
rng_bytes=0

SCRIPT_START=$(date +"%s.%N")
for i in `seq $N`
do
	START=$(date +"%s.%N")
	r=$(( ($RANDOM % $blim) + 1 ))
	rng_bytes=$(( $rng_bytes + $r ))
	head -c $r </dev/urandom > $tmp
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
		echo -e "\n${C_RED}ERROR${C_EOC}"
		exit 1
	fi
	CURRENT=$(date +"%s.%N")
    timediff $SCRIPT_START $CURRENT
	averages $rt $ot $fst $rng_bytes $i
    print_status_bar $TIME_DIFF $i $N "\r"
done
print_status_bar $TIME_DIFF $i $N "\n"
prc=$(echo "scale=6; ($A_FTSSL / $A_ORIG) * 100" | bc)
printf "${C_GREEN}Success${C_EOC} | FT_SSL relative speed %.2f%% | AVG file size: %d\n" $prc $A_RNGBYTE
rm $tmp $orig $res