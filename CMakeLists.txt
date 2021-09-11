cmake_minimum_required(VERSION 3.20)
project(bank_management C)

set(CMAKE_C_STANDARD 11)

add_executable(bank_management bank_management.c bank.c)
