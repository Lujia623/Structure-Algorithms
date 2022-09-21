cmake_minimum_required(VERSION 3.15)
project(Clion C)

set(CMAKE_C_STANDARD 99)
#
aux_source_directory(${PROJECT_SOURCE_DIR} MAIN_PATH)
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(Clion main.c src/ADT_List.c inc/ADT_List.h inc/Base_Type.h inc/fifo.h src/STACK_QUEUE.c inc/STACK_QUEUE.h src/ADT_String.c inc/ADT_String.h src/Function_Test.c inc/Function_Test.h src/ADT_Tree.c inc/ADT_Tree.h)

# 指定 cmake 最低编译版本
#CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
#PROJECT (MATH)
# 把当前工程目录下的 src 目录的下的所有 .cpp 和 .c 文件赋值给 SRC_LIST
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src ADT_List)
FILE(GLOB ADT_List "SOURCES/src/*.c")
# 打印 SRC_LIST 文件列表
MESSAGE(STATUS ${ADT_List})
# 指定头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/inc)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src ADT_List)
#ADD_LIBRARY(qq SHARED ${SRC_LIST})# 指定生成动态库
ADD_LIBRARY(ADT_List STATIC ${ADT_List} src/ADT_String.c inc/ADT_String.h)# 指定生成静态库
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)# 指定输出 .so 动态库的目录位置

#连接库
#aux_source_directory(${CMAKE_SOURCE_DIR} ROOTPATH_ALL_SRC)# 这里对 ${CMAKE_SOURCE_DIR} 也就是当前CMakeList.txt 目录下的*.cpp输出到变量 ,RP_ALL_SRC （ROOTPATH_ALL_SRC 意为顶层目录所有源码）
##add_executable(Clion main.c lib/qq.c)
#target_link_libraries(Clion qq)
# 指定生成版本号，VERSION指代动态库版本，SOVERSION指代API版本
# SET_TARGET_PROPERTIES(math PROPERTIES VERSION 1.2 SOVERSION 1)