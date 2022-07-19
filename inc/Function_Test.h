//
// Created by ASUS on 2022/5/9 0009.
//

#ifndef CLION_FUNCTION_TEST_H
#define CLION_FUNCTION_TEST_H

#include "ADT_List.h"
#include "STACK_QUEUE.h"
#include "ADT_String.h"
#include "ADT_Tree.h"

void __attribute__((weak)) SequentialList_FunctionTest(void)
{
    printf("%s not reimplemented!!!\n",__FUNCTION__);
}

void __attribute__((weak)) MallocList_FunctionTest(void)
{
    printf("%s not reimplemented!!!\n",__FUNCTION__);
}

void __attribute__((weak)) StaticList_FunctionTest(void)
{
    printf("%s not reimplemented!!!\n",__FUNCTION__);
}

void __attribute__((weak)) CycleList_FunctionTest(void)
{
    printf("%s not reimplemented!!!\n",__FUNCTION__);
}

void __attribute__((weak)) DoubleList_FunctionTest(void)
{
    printf("%s not reimplemented!!!\n",__FUNCTION__);
}

//#define ADT_LIST_CLOSE  0
//#define ADT_LIST_OPEN   1

void Function_Test(void);

#endif //CLION_FUNCTION_TEST_H
