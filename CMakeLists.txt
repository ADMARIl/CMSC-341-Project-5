cmake_minimum_required(VERSION 3.12)
project(proj5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj5
        Driver.cpp
        HashTable.cpp
        HashTable.h
        primes.cpp
        #[[test1.cpp
        test1.txt
        test2.cpp
        #[[test2.txt
        test3.cpp
        test3.txt
        test4.cpp
        test4.txt
        test5.cpp
        test5.txt]]
        words.h)
