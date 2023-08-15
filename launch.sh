#!/bin/bash

cd src/

c++ -std=c++11 -pthread *.cpp -o HSBC

./HSBC