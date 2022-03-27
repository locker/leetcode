#!/bin/sh

FILE=file.txt
NF=$(head -n1 "$FILE" | awk '{print NF}')
for i in $(seq 1 "$NF"); do
    cat "$FILE" | awk "{print \$$i}" | head -c-1 | tr '\n' ' '
    echo
done
