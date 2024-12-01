#!/bin/bash

nasm -f elf encode64.s -o encode64.o
nasm -f elf decode64.s -o decode64.o
gcc -m32 -o main main.c encode64.o decode64.o
