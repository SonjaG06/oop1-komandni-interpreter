cmake_minimum_required(VERSION 4.0)
project(projekat)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekat main.cpp
        Command.cpp
        Command.h
        Date.cpp
        Date.h
        Echo.cpp
        Echo.h
        Interpreter.cpp
        Interpreter.h
        Parser.cpp
        Parser.h
        Time.cpp
        Time.h
        Touch.cpp
        Touch.h
        WordCount.cpp
        WordCount.h
        Prompt.cpp
        Prompt.h
        Remove.cpp
        Remove.h
        Translate.cpp
        Translate.h
        Head.cpp
        Head.h
        Batch.cpp
        Batch.h
        Exception.cpp
        Exception.h
        Truncate.cpp
        Truncate.h
)
