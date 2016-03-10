#!/bin/sh
set -x #echo on

g++ -Wall -std=c++11 -O2 -pthread futex.cpp -o futex
g++ -Wall -std=c++11 -O2 -pthread mutex.cpp -o mutex

time ./futex 4
time ./mutex 4

time ./futex 2
time ./mutex 2

time ./futex 8
time ./mutex 8