#!/bin/sh
    rm build/NIDS
    gcc src/*.c -lrt -ldl -lpthread -I./include -o build/NIDS
