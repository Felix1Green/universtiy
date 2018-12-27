#!/bin/bash

function winkoi
{
num=

for i in ${num[*]} ; do 
low=$low";\3$i"; 
up=$up";\3`expr $i + 40`"; 
done
echo $up$low 
return 
}
if test $# -lt 2 
then echo "Usage: `basename $0` input.win output.koi"; ; exit −7
fi
if ! test -f $1 # Проверка существования входного файла
then echo "$1: No such regular file" >&2; exit 2 # ENOENT
fi
if ! test -r $1 # Контроль доступа по чтению для входного файла
then echo "$1: Permission denied to read" >&2 ; exit 13 # EACCES
fi
# Контроль маршрутного имени для выходного файла
curdir=`pwd` 
outdir=`expr $2 : &#39;\(.*/\)&#39; \| $curdir` # маршрутное имя каталога
if [ ! -w $outdir -a ! -e $2 ] # контроль каталога по (пере)записи
then echo "$outdir: Permission denied to write" >&2 ; exit -13
fi
if test -d $2 
then echo "$2: Is directory" >&2 ; exit 21 # EISDIR
fi
if [ -e $2 -a ! -w $2 ] # Контроль перезаписи выходного файла
then echo "$2: Permission denied to rewrite" ; exit 13 # EACCES
fi
cat $1 | tr "\300-\337\340-\377" `winkoi` > $2
exit 0 # Нормальное завершение программы
