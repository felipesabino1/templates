#!/bin/bash

make brute
make gen
make at # codigo que muda

while true; do
    ./gen 2 > in
    
    start=$(date +%s)
    ./at < in > out # codigo que muda
    end=$(date +%s)

    echo "Elapsed Time in test $c: $(($end - $start)) seconds."
    ./brute < in > aout
    diff -B out aout > /dev/null || break
    echo "Passou no caso $c."
    cat out
done

echo "WA on the following case:"
cat in
echo "Your answer is:"
cat out
echo "Correct answer is:"
cat aout
