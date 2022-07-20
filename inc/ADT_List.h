//
// Created by Rougga on 2022/4/16 0016.
//

#ifndef CLION_ADT_LIST_H
#define CLION_ADT_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include "Base_Type.h"

#pragma pack(4)

#define SEQ_MAX_SIZE 20         //顺序存储结构大小
#define STATIC_MAX_SIZE 1000    //静态链式存储结构大小

#define INIT_MALLOC_ONE_OR_TWO  1   //1:way one 0:way two

#define ADT_LIST_CLOSE              BIT(0)               //关闭所有
#define USE_STATIC_LIST             BIT(1)               //静态链表
#define USE_MALLOC_LIST             BIT(2)               //动态链表(单链表)
#define USE_CYCLE_LIST              BIT(3)               //动态链表(循环链表,单链表)
#define USE_SEQUENTIAL_LIST         BIT(4)               //顺序表
#define USE_DOUBLE_LIST             BIT(5)               //双向链表(循环链表)
#define USE_ADT_LIST_WAYS           (USE_STATIC_LIST | USE_MALLOC_LIST     \
                                    | USE_CYCLE_LIST | USE_SEQUENTIAL_LIST | USE_DOUBLE_LIST)
//#define USE_ADT_LIST_WAYS           ADT_LIST_CLOSE

/**
 * @brief 线性表链式存储结构(动态)
 *
 */
typedef struct sList{
    struct sList *next;
    int num;
} sList;

/**
 * @brief 线性表双向链表
 * 
 */
typedef struct List
{
    struct List* next;
    struct List* previous;
    int data;
}sDoubleList;


/**
 * @brief 线性表链式存储结构(静态)
 *
 */
typedef struct {
    ElemType data;  //数据
    int cursor;     //游标
} sStaticList,StaticLinkList[STATIC_MAX_SIZE];

/**
 * @brief 线性表顺序存储结构
 * 
 */
typedef struct {
    ElemType data[SEQ_MAX_SIZE];
    int length;
}SqList;

#if USE_ADT_LIST_WAYS & USE_MALLOC_LIST

/**
 * @brief Create a List Head object
 * 
 * @param iList 传入的指针变量
 * @param num 链表节点数量
 */
void CreateListHead(sList **iList, int num);

/**
 * @brief Create a List Tail object
 * 
 * @param iList 传入的指针变量
 * @param num 链表节点数量
 */
void CreateListTail(sList **iList,int num);

/**
 * @brief 以尾插法插入
 * 
 * @param iList 指针变量
 * @param iPosition 插入位置
 * @param element 数据域中的值
 */
void ListInsertHead(sList **iList,int iPosition,int element);

/**
 * @brief 以头插法插入
 * 
 * @param iList 指针变量
 * @param iPosition 插入位置
 * @param element 数据域中的值
 */
void ListInsertTail(sList **iList, int iPosition, int element);

/**
 * @brief 查找中间节点的值
 * 
 * @param iList 指针变量
 * @param element 存放中间节点的值
 */
void SearchMidList(sList *iList,int *element);

/**
 * @brief Get the Element object
 * 
 * @param iList 指针变量
 * @param element 查找值
 * @return sList* 返回节点指针
 */
sList *GetElement(sList *iList,int element);

/**
 * @brief Get the Same Element object
 * 
 * @param iList 指针变量
 * @param element 查找值
 * @return sList*  返回一个新的单链表
 */
sList *GetSameElement(sList *iList,int element);

/**
 * @brief 删除指定节点
 * 
 * @param iList 指针变量
 * @param iPosition 删除位置
 * @param element 存放删除节点数据域中的值
 */
void ListDelete(sList **iList,int iPosition,int *element);

/**
 * @brief 整表清除
 * 
 * @param iList 指针变量
 * @return true success
 * @return false fail
 */
bool ClearList(sList **iList);

/**
 * @brief 单链表打印
 * 
 * @param iList 指针变量
 */
void ShowList(sList **iList);

/**
 * @brief 初始化单链表
 * 
 * @param list 指向头结点指针
 */
bool InitList(sList** iList);

/**
 * @brief 创建一个数据域为value的节点
 * 
 * @param value 
 * @return sList* 返回节点指针
 */
sList *CreatNode(int value);

/**
 * @brief 判断链表是否为空
 * 
 * @param list 头结点
 * @return true 空链表
 * @return false 非空链表
 */
bool ListEmpty(sList *list);

/**
 * @brief 动态链表模块测试接口
 * 
 */
void MallocList_FunctionTest(void);
#endif

///单链表循环链表
#if USE_ADT_LIST_WAYS & USE_CYCLE_LIST

/**
 * @brief 初始化循环链表
 * 
 * @param iList sList指针变量
 */
void InitCycleList(sList **iList);

/**
 * @brief 创建循环链表
 * 
 * @param iList sList指针变量
 * @param num 节点数量
 */
void CreatCycleList(sList **iList, int num);

/**
 * @brief Get the Cycle List Length object
 * 
 * @param iList sList指针变量
 * @return int 返回循环链表长度
 */
int GetCycleListLength(sList *iList);

/**
 * @brief 循环链表插入
 * 
 * @param iList sList指针变量
 * @param iPosition 插入位置
 * @param element 插入值
 */
void CycleListInsert(sList **iList, int iPosition, int element);

/**
 * @brief 
 * 
 * @param iList 
 * @param iPosition 
 * @param element 
 */
void CycleListDelete(sList **iList, int iPosition, int *element);

/**
 * @brief 单链表循环链表打印
 * 
 * @param iList sList指针变量
 */
void ShowCycleList(sList **iList);

/**
 * @brief 单链表循环链表模块测试接口
 * 
 */
void CycleList_FunctionTest(void);
#endif

#if USE_ADT_LIST_WAYS & USE_DOUBLE_LIST

/**
 * @brief 创建双向链表(循环结构)
 * 
 * @param iList sDoubleList指针变量
 * @param num 节点数量
 * @return true 创建成功
 * @return false 创建失败
 */
bool CreatDoubleList(sDoubleList **iList, int num);

/**
 * @brief Get the Double List Length object
 * 
 * @param iList sDoubleList指针变量
 * @return int 节点个数
 */
int GetDoubleListLength(sDoubleList *iList);

/**
 * @brief 双向链表插入
 * 
 * @param iList sDoubleList指针变量
 * @param iPosition 插入位置
 * @param element 插入的元素值
 * @return true 插入成功
 * @return false 插入失败
 */
bool DoubleListInsert(sDoubleList **iList, int iPosition, int element);

/**
 * @brief 双向链表删除
 * 
 * @param iList sDoubleList指针变量
 * @param iPosition 删除位置
 * @param element 存放删除节点中的元素值
 * @return true 删除成功
 * @return false 删除失败
 */
bool DoubleListDelete(sDoubleList **iList, int iPosition, int *element);

/**
 * @brief 双向链表整表删除
 * 
 * @param iList sDoubleList指针变量
 */
void ClearDoubleList(sDoubleList **iList);

/**
 * @brief 双向链表打印
 * 
 * @param iList sDoubleList指针变量
 */
void ShowDoubleList(sDoubleList **iList);

/**
 * @brief 双向链表循环链表模块测试接口
 * 
 */
void DoubleList_FunctionTest(void);
#endif

#if USE_ADT_LIST_WAYS & USE_STATIC_LIST

/**
 * @brief Get the Idle Index object 获取备用静态链表下标
 * 
 * @param space StaticLinkList 静态链表(数组)
 * @return int 返回备用静态链表下标
 */
int GetIdleIndex(StaticLinkList space);

/**
 * @brief 初始化静态链表
 * 
 * @param space StaticLinkList 静态链表(数组)
 */
void InitStaticLinkList(StaticLinkList space);

/**
 * @brief 创建静态链表
 * 
 * @param space StaticLinkList 静态链表(数组)
 * @param num 静态链表节点个数
 */
void CreatStaticList(StaticLinkList space, int num);

/**
 * @brief Get the Static List Length object
 * 
 * @param space StaticLinkList 静态链表(数组)
 * @return int 静态链表节点个数
 */
int GetStaticListLength(StaticLinkList space);

/**
 * @brief 静态链表插入
 * 
 * @param space StaticLinkList 静态链表(数组)
 * @param iPosition 插入位置
 * @param element 元素值
 */
void InsertStaticList(StaticLinkList space, int iPosition, int element);

/**
 * @brief 静态链表整表删除
 * 
 * @param space  StaticLinkList 静态链表(数组)
 * @param iPosition 删除位置
 */
void DeleteStaticList(StaticLinkList space, int iPosition);

/**
 * @brief 静态链表打印
 * 
 * @param space StaticLinkList 静态链表(数组)
 */
void ShowStaticList(StaticLinkList space);

/**
 * @brief 静态链表模块测试接口
 * 
 */
void StaticList_FunctionTest(void);
#endif

#if USE_ADT_LIST_WAYS & USE_SEQUENTIAL_LIST

/**
 * @brief 创建顺序表顺序存储结构
 * 
 * @param list 顺序表顺序结构指针
 * @param len 数量
 */
void CreatSequentialList(SqList *iList, int len);

/**
 * @brief 顺序表顺序存储插入
 * 
 * @param iList 顺序存储结构体
 * @param iPosition 插入位置
 * @param element 插入的元素值
 * @return true 插入成功
 * @return false 插入失败
 */
bool SequentialListInsert(SqList *iList, int iPosition, int element);

/**
 * @brief 打印顺序表中的值
 * 
 * @param iList 顺序存储结构体
 */
void ShowSequentialList(SqList *iList);

/**
 * @brief 顺序存储测试接口
 * 
 */
void SequentialList_FunctionTest(void);
#endif

#endif //CLION_ADT_LIST_H
