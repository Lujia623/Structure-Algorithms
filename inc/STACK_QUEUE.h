//
// Created by Rougga on 2022/5/9 0009.
//

#ifndef CLION_STACK_QUEUE_H
#define CLION_STACK_QUEUE_H

#include "Base_Type.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#pragma pack(8)

#define USE_STACK   1
#define USE_QUEUE   1

#define USE_MOLLOC_STACK        1
#define USE_LIST_STACK          2
#define USE_SEQUENTIAL_STACK    3

#define USE_LIST_QUEUE          4
#define USE_LIST_CYCLE_QUEUE    5
#define USE_SEQUENTIAL_QUEUE    6

#define USE_STACK_WAY     USE_MOLLOC_STACK
#define USE_QUEUE_WAY     USE_LIST_CYCLE_QUEUE
#define STACK_MAX_SIZE    100

typedef struct statck
{
    ElemType data[STACK_MAX_SIZE];
    int top;//栈顶
}sStack;

typedef struct Stack{
    int* bottom;
    int* top;
    int stack_length;
}SqStack;

typedef struct StackNode
{
    ElemType data;
    struct StackNode* next;
}sStackNode;

typedef struct LinkStack
{
    sStackNode * top;
    int length;
}sLinkStack;

typedef struct QueueNode
{
    ElemType data;
    struct QueueNode* next;
}sQueueNode;

typedef struct LinkQueue
{
    sQueueNode* fifo_in;
    sQueueNode* fifo_out;
    int length;
}sLinkQueue;

#if USE_STACK_WAY == USE_SEQUENTIAL_STACK
/**
 * @brief 初始化栈
 * 
 * @param iStack 
 * @return true 初始化成功
 * @return false 初始化失败
 */
bool InitStack(sStack* iStack);

/**
 * @brief 进栈
 * 
 * @param iStack 
 * @param element 
 * @return true 进栈成功
 * @return false 进栈失败
 */
bool push(sStack* iStack,ElemType element);

/**
 * @brief 出栈
 * 
 * @param iStack 
 * @param element 
 * @return true 
 * @return false 
 */
bool pop(sStack* iStack,ElemType* element);

/**
 * @brief 获取栈的长度
 * 
 * @param iStack 
 * @return int 
 */
int StackLength(sStack iStack);

/**
 * @brief 清空栈
 * 
 * @param iStack 
 */
void ClearStack(sStack iStack);

#elif USE_STACK_WAY == USE_MOLLOC_STACK
bool InitStack(SqStack* iStack);
bool push(SqStack* iStack,ElemType element);
bool pop(SqStack* iStack,ElemType* element);
int StackLength(SqStack iStack);
bool Stack_is_Empty(SqStack iStack);
void ClearStack(SqStack *iStack);
void DestroyStack(SqStack* iStack);
int GetTop(SqStack iStack);

#elif USE_STACK_WAY == USE_LIST_STACK
bool InitStack(sLinkStack* iLinkStack);
bool push(sLinkStack* iLinkStack,ElemType element);
bool pop(sLinkStack* iLinkStack,ElemType* element);
int StackLength(sLinkStack iLinkStack);
void DestroyStack(sLinkStack* iLinkStack);
int GetTop(sLinkStack iLinkStack);

#endif

#if USE_QUEUE_WAY == USE_LIST_QUEUE
void InitQueue(sLinkQueue* iLinkQueue);
void InQueue(sLinkQueue* iLinkQueue,ElemType element);
void OutQueue(sLinkQueue* iLinkQueue,ElemType* element);
void DestroyQueue(sLinkQueue* iLinkQueue);
bool QueueEmpty(sLinkQueue iLinkQueue);
ElemType GetHead(sLinkQueue* iLinkQueue);

#elif USE_QUEUE_WAY == USE_LIST_CYCLE_QUEUE
void InitQueue(sLinkQueue* iLinkQueue);
void InQueue(sLinkQueue* iLinkQueue,ElemType element);
void OutQueue(sLinkQueue* iLinkQueue,ElemType* element);
bool QueueEmpty(sLinkQueue iLinkQueue);
#elif USE_QUEUE_WAY == USE_SEQUENTIAL_QUEUE

#endif

void Stack_FunctionTest(void);

#endif //CLION_STACK_QUEUE_H
