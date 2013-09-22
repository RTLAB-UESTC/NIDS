#!/bin/sh
    rm build/NIDS
    g++  src/*.cpp -lrt -ldl -lpthread -I./include -o build/NIDS
