CMAKE_MINIMUM_REQUIRED(VERSION 2.6) #限制cmake版本
PROJECT(perlin_noise)#定义项目名称
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()
AUX_SOURCE_DIRECTORY(. DIR_SRCS)#将当前目录中的源文件名称赋值给变量 DIR_SRCS
ADD_EXECUTABLE(perlin_noise ${DIR_SRCS})#变量 DIR_SRCS 中的源文件需要编译 成一个名称为hello的可执行文件