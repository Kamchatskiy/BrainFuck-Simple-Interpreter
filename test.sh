#!/bin/bash
gcc src/main.c -o prog
chmod +x prog
for file in ./tests/*; do
    ./prog "$file"
done
rm prog