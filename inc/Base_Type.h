//
// Created by ASUS on 2022/4/17 0017.
//

#ifndef CLION_BASE_TYPE_H
#define CLION_BASE_TYPE_H


typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef _Bool bool;
typedef int ElemType;

#define BIT(x)               (1 << x)

#define true                 (bool)1
#define false                !true
#define ENABLE               (bool)1
#define DISABLE !ENABLE



#endif //CLION_BASE_TYPE_H
