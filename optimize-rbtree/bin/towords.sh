#!/bin/sh

[ $# -eq 0 ] && echo "I need a file name" && exit 1
ici=$(dirname $0)
bin=cmake-build-debug/optimize_rbtree

while [ $# -ne 0 ]
do
  in=$1
  out=$1.out
  words=${in}.words
  ref=${in}.ref

  dos2unix $1
  sed 's/[,;:\.\?\-\*\+"“’‘_—£”!$]/ /g' ${in} | \
   tr -s '[](){}-' ' '  | \
    tr 'éèêë' 'e' | \
     tr 'àâä' 'a' | \
       ${ici}/towords.awk > ${words}
  cat $words | sort | uniq -c > ${ref}
  ${bin} ${words} > ${out}
  diff -y --suppress-common-lines ${ref} ${out}
  shift
done
