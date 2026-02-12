cmake_minimum_required(VERSION 3.10)
project(TextLab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TextLab2
    main.cpp
    producer.cpp
    consumer.cpp
)
