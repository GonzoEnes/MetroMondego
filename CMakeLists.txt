cmake_minimum_required(VERSION 3.22)
project(MetroMondego C)

set(CMAKE_C_STANDARD 99)

add_executable(MetroMondego main.c paragens.c paragens.h linhas.c linhas.h fileHandling.c menu.c menu.h utils.c utils.h fileHandling.h)
