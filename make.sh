#!/bin/bash

gcc -Wall -Wpedantic -g3 -lm -lglfw  -lGL -lX11 -lpthread -lXrandr -lXi -ldl  -o pong ping-pong.c
