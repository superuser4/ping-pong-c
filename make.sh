#!/bin/bash

gcc -Wall -Wpedantic -Wextra -Werror -g3 -lGL -lglfw  -o pong src/ping-pong.c
