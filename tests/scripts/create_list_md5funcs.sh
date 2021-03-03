#! /bin/bash

N=$1
RANDOM=$(date +%N)
OUT_PREF=$2

## HEAD F
echo -e "#include \"test.h\"

static void unittest_md5f_one(uint32_t b, uint32_t c, uint32_t d,
								uint32_t expected, int *current, int total)
{
	uint32_t ret;

	*current += 1;
	ret = ft_md5_f(b, c, d);
	assert(ret == expected);
	STATUS(*current, total);
}

void unittest_md5f()
{
	int current = 0;
	int total = $N;

	CATEGORY(\"ft_md5_f\");" > ${OUT_PREF}f.c

## HEAD G
echo -e "#include \"test.h\"

static void unittest_md5g_one(uint32_t b, uint32_t c, uint32_t d,
								uint32_t expected, int *current, int total)
{
	uint32_t ret;

	*current += 1;
	ret = ft_md5_g(b, c, d);
	assert(ret == expected);
	STATUS(*current, total);
}

void unittest_md5g()
{
	int current = 0;
	int total = $N;

	CATEGORY(\"ft_md5_g\");" > ${OUT_PREF}g.c

## HEAD H
echo -e "#include \"test.h\"

static void unittest_md5h_one(uint32_t b, uint32_t c, uint32_t d,
								uint32_t expected, int *current, int total)
{
	uint32_t ret;

	*current += 1;
	ret = ft_md5_h(b, c, d);
	assert(ret == expected);
	STATUS(*current, total);
}

void unittest_md5h()
{
	int current = 0;
	int total = $N;

	CATEGORY(\"ft_md5_h\");" > ${OUT_PREF}h.c

## HEAD I
echo -e "#include \"test.h\"

static void unittest_md5i_one(uint32_t b, uint32_t c, uint32_t d,
								uint32_t expected, int *current, int total)
{
	uint32_t ret;

	*current += 1;
	ret = ft_md5_i(b, c, d);
	assert(ret == expected);
	STATUS(*current, total);
}

void unittest_md5i()
{
	int current = 0;
	int total = $N;

	CATEGORY(\"ft_md5_i\");" > ${OUT_PREF}i.c

for i in `seq $N`
do
	declare -i b=$(( (($RANDOM*$RANDOM*($RANDOM%11))%4294967296) - 2147483648 ))
	declare -i c=$(( (($RANDOM*$RANDOM*($RANDOM%11))%4294967296) - 2147483648 ))
	declare -i d=$(( (($RANDOM*$RANDOM*($RANDOM%11))%4294967296) - 2147483648 ))
	f=$(( ($b&$c)|(~$b&$d) ))
	echo -e "\tunittest_md5f_one($b, $c, $d, $f, &current, total);" >> ${OUT_PREF}f.c
	f=$(( ($b&$d)|($c&~$d) ))
	echo -e "\tunittest_md5g_one($b, $c, $d, $f, &current, total);" >> ${OUT_PREF}g.c
	f=$(( $b^$c^$d ))
	echo -e "\tunittest_md5h_one($b, $c, $d, $f, &current, total);" >> ${OUT_PREF}h.c
	f=$(( $c^($b|~$d) ))
	echo -e "\tunittest_md5i_one($b, $c, $d, $f, &current, total);" >> ${OUT_PREF}i.c
done

## TAIL F
echo "}" >> ${OUT_PREF}f.c

## TAIL G
echo "}" >> ${OUT_PREF}g.c

## TAIL H
echo "}" >> ${OUT_PREF}h.c

## TAIL I
echo "}" >> ${OUT_PREF}i.c