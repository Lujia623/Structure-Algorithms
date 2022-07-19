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

#define ADT_STACK_QUEUE_CLOSE   BIT(0)

#define USE_MOLLOC_STACK        BIT(1)
#define USE_LIST_STACK          BIT(2)
#define USE_SEQUENTIAL_STACK    BIT(3)

#define USE_LIST_QUEUE          BIT(4)
#define USE_LIST_CYCLE_QUEUE    BIT(5)
#define USE_SEQUENTIAL_QUEUE    BIT(6)

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
/**
 * @brief 初始化由malloc分配一块固定大小的内存
 * 
 * @param iStack SqStack数据变量
 * @return true 初始化成功
 * @return false 初始化失败
 */
bool InitStack(SqStack* iStack);

/**
 * @brief 入栈操作
 * 
 * @param iStack SqStack数据变量
 * @param element 数据域值
 * @return true push成功
 * @return false push失败
 */
bool push(SqStack* iStack,ElemType element);

/**
 * @brief 出栈操作
 * 
 * @param iStack SqStack数据变量
 * @param element 数据域值
 * @return true pop成功
 * @return false pop失败
 */
bool pop(SqStack* iStack,ElemType* element);

/**
 * @brief 获取栈的长度
 * 
 * @param iStack SqStack数据变量
 * @return int 返回栈的长度 
 */
int StackLength(SqStack iStack);

/**
 * @brief 栈是否为空
 * 
 * @param iStack SqStack数据变量
 * @return true 为空
 * @return false 非空
 */
bool Stack_is_Empty(SqStack iStack);

/**
 * @brief 清空栈
 * 
 * @param iStack SqStack数据变量
 */
void ClearStack(SqStack *iStack);

/**
 * @brief 销毁栈
 * 
 * @param iStack SqStack数据变量
 */
void DestroyStack(SqStack* iStack);

/**
 * @brief Get the Top object
 * 
 * @param iStack SqStack数据变量
 * @return int 栈顶数据域元素
 */
int GetTop(SqStack iStack);

#elif USE_STACK_WAY == USE_LIST_STACK
/**
 * @brief 初始化链表栈,栈的增长方向和链表节点增长方向相反
 * 
 * @param iLinkStack sLinkStack指向栈顶和记录栈的长度
 * @return true 初始化成功
 * @return false 初始化失败
 */
bool InitStack(sLinkStack* iLinkStack);

/**
 * @brief 入栈操作
 * 
 * @param iLinkStack sLinkStack指向栈顶和记录栈的长度
 * @param element 入栈数据域元素
 * @return true push成功
 * @return false push失败
 */
bool push(sLinkStack* iLinkStack,ElemType element);

/**
 * @brief 出栈操作
 * 
 * @param iLinkStack sLinkStack指向栈顶和记录栈的长度
 * @param element 出栈数据域元素
 * @return true pop成功
 * @return false pop失败
 */
bool pop(sLinkStack* iLinkStack,ElemType* element);

/**
 * @brief 获取栈的长度
 * 
 * @param iLinkStack sLinkStack指向栈顶和记录栈的长度
 * @return int 返回栈的长度
 */
int StackLength(sLinkStack iLinkStack);

/**
 * @brief 销毁栈
 * 
 * @param iLinkStack sLinkStack指向栈顶和记录栈的长度
 */
void DestroyStack(sLinkStack* iLinkStack);

/**
 * @brief Get the Top object
 * 
 * @param iLinkStack sLinkStack指向栈顶和记录栈的长度
 * @return int 栈顶数据域元素
 */
int GetTop(sLinkStack iLinkStack);

#endif

#if USE_QUEUE_WAY == USE_LIST_QUEUE
/**
 * @brief 循环队列,其节点是单向链表
 * 
 * @param iLinkQueue sLinkQueue
 */
void InitQueue(sLinkQueue* iLinkQueue);

/**
 * @brief 入队列操作
 * 
 * @param iLinkQueue sLinkQueue
 * @param element 入队元素
 */
void InQueue(sLinkQueue* iLinkQueue,ElemType element);

/**
 * @brief 出队列操作
 * 
 * @param iLinkQueue sLinkQueue
 * @param element 出队列数据域元素
 */
void OutQueue(sLinkQueue* iLinkQueue,ElemType* element);

/**
 * @brief 销毁队列
 * 
 * @param iLinkQueue sLinkQueue
 */
void DestroyQueue(sLinkQueue* iLinkQueue);

/**
 * @brief 判定队列是否为空
 * 
 * @param iLinkQueue sLinkQueue
 * @return true 队列为空
 * @return false 队列非空
 */
bool QueueEmpty(sLinkQueue iLinkQueue);

/**
 * @brief Get the Head object
 * 
 * @param iLinkQueue sLinkQueue
 * @return ElemType 队列顶部元素
 */
ElemType GetHead(sLinkQueue* iLinkQueue);

#elif USE_QUEUE_WAY == USE_LIST_CYCLE_QUEUE
/**
 * @brief 循环队列,其节点循环链表构成
 * 
 * @param iLinkQueue sLinkQueue
 */
void InitQueue(sLinkQueue* iLinkQueue);

/**
 * @brief 入队操作
 * 
 * @param iLinkQueue sLinkQueue
 * @param element 入队元素
 */
void InQueue(sLinkQueue* iLinkQueue,ElemType element);

/**
 * @brief 出队操作
 * 
 * @param iLinkQueue sLinkQueue
 * @param element 出队元素
 */
void OutQueue(sLinkQueue* iLinkQueue,ElemType* element);

/**
 * @brief 判定队列是否为空
 * 
 * @param iLinkQueue sLinkQueue
 * @return true 队列为空
 * @return false 队列非空
 */
bool QueueEmpty(sLinkQueue iLinkQueue);
#elif USE_QUEUE_WAY == USE_SEQUENTIAL_QUEUE

#endif

/**
 * @brief 栈测试接口
 * 
 */
void Stack_FunctionTest(void);

#endif //CLION_STACK_QUEUE_H
