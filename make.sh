#!/bin/bash

gcc -Wall -Wextra -g3 -lGL -lglfw  -lm -o pong src/ping-pong.c src/glad.c
