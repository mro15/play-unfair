#! /bin/bash

cat /usr/share/dict/brazilian | \
sed -e 's/ç/c/g' | \
sed -e 's/â/a/g' | \
sed -e 's/ã/a/g' | \
sed -e 's/á/a/g' | \
sed -e 's/à/a/g' | \
sed -e 's/ä/a/g' | \
sed -e 's/é/e/g' | \
sed -e 's/ê/e/g' | \
sed -e 's/ë/e/g' | \
sed -e 's/í/i/g' | \
sed -e 's/ï/i/g' | \
sed -e 's/ó/o/g' | \
sed -e 's/ô/o/g' | \
sed -e 's/õ/o/g' | \
sed -e 's/ö/o/g' | \
sed -e 's/ú/u/g' | \
sed -e 's/ü/u/g' | \
sed -e 's/Â/A/g' | \
sed -e 's/Ã/A/g' | \
sed -e 's/Á/A/g' | \
sed -e 's/À/A/g' | \
sed -e 's/É/E/g' | \
sed -e 's/Ê/E/g' | \
sed -e 's/Í/I/g' | \
sed -e 's/Ï/I/g' | \
sed -e 's/Ó/O/g' | \
sed -e 's/Ô/O/g' | \
sed -e 's/Õ/O/g' | \
sed -e 's/Ö/O/g' | \
sed -e 's/Ú/U/g' | \
sed -e 's/Ü/U/g' | \
tr [A-Z] [a-z] | \
egrep .... | \
egrep -v ....... > dict.txt
