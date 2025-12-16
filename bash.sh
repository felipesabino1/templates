#!/bin/bash

make brute
make gen
make at # codigo que muda

while true; do
    ./gen 2 > in
    ./at < in > out # codigo que muda

    ./brute < in > aout
    diff -B out aout > /dev/null || break
    echo "Passou"
    cat out
done

echo "WA:"
cat in
echo "Your answer:"
cat out
echo "Correct answer:"
cat aout
