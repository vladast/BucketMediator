cmake_minimum_required(VERSION 2.8)

project(BucketMediator)

find_package(AWSSDK REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
