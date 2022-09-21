#cmake_minimum_required(VERSION 3.15)
#project(Clion C)
#
#set(CMAKE_C_STANDARD 99)
#
#
#AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/ SRC_LIST)
# FILE(GLOB SRC_LIST "SOURCES/src/*.c")
# # 打印 SRC_LIST 文件列表
# MESSAGE(STATUS ${SRC_LIST})
# # 指定头文件目录
# INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/inc)
#
#
# #ADD_LIBRARY(qq SHARED ${SRC_LIST})# 指定生成动态库
## ADD_LIBRARY(qq STATIC ${SRC_LIST})# 指定生成静态库
## SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)# 指定输出 .so 动态库的目录位置
#
# add_executable(Clion qq.c)