#!/bin/bash

gcc -Wall -Wextra -g3 -lGL -lglfw -lm -lglut -static -o pong src/ping-pong.c src/glad.c
