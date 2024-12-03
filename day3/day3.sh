#!/bin/sh

result=0

for i in $(grep -o "mul([0-9]*,[0-9]*)" data.input | sed 's/mul(\([0-9]*\),\([0-9]*\))/\1*\2/')
do
    result=$((result+${i}))
done

echo "${result}"

exit 0
