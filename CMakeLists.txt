cmake_minimum_required(VERSION 3.10)
project(maria_cherkasova)

set(CMAKE_CXX_STANDARD 11)

add_executable(main
        main.cpp Deque.h DequeIterator.h OutOfRangeException.h Algorithm.h)
