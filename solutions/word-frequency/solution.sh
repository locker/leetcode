#!/bin/sh

cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -rk1 | awk '{print $2, $1}'
