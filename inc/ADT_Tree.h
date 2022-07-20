//
// Created by Rougga on 2022/7/11 0011.
//

#ifndef CLION_ADT_TREE_H
#define CLION_ADT_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include "Base_Type.h"

#pragma pack(4)

#define ADT_TREE_CLOSE       BIT(0)           //关闭所有
#define PARENTS_CHILDS_WAYS  BIT(1)          //数的双亲表示法
#define BINARY_TREE          BIT(2)          //二叉树

#define USE_ADT_TREE_WAYS    (PARENTS_CHILDS_WAYS | BINARY_TREE)
//#define USE_ADT_TREE_WAYS    ADT_TREE_CLOSE

#if (USE_ADT_TREE_WAYS == PARENTS_CHILDS_WAYS)
#define MAX_TREE_SIZE   100
typedef struct CTNode {      //孩子节点
    int child;              //孩子节点位置
    struct CTNode *next;    //同一层孩子链表
} *ChildPtr;
typedef struct {            //表头结构
    int data;               //数据域
    ChildPtr firstchild;    //孩子链表头指针
} CTBox;
typedef struct {
    CTBox nodes[MAX_TREE_SIZE];       //节点数组
    int r, n;                        //根的位置和节点数
} CTree;
#endif

#if USE_ADT_TREE_WAYS & BINARY_TREE
typedef struct Binary_Node {
    int data;                                        //二叉树的节点数据域
    struct Binary_Node *left_node, *right_node;      //二叉树左右孩子指针
} BinaryTreeNode, *BinaryTreePtr;                   //BinaryTreeNode:节点,BinaryTreePtr:头指针

/*构建二叉树层序遍历架构,循环队列,单向循环链表*/
typedef struct TreeQueueNode {
    BinaryTreeNode treeNode;
    struct TreeQueueNode *next;
} sTreeQueueNode;
typedef struct TreeLinkQueue {
    sTreeQueueNode *fifo_in;
    sTreeQueueNode *fifo_out;
} sTreeLinkQueue;

/**
 * @brief 二叉树插入操作
 * 
 * @param iTreeRoot 指向根节点
 * @param idata 插入值
 */
void InsertTree(BinaryTreePtr *iTreeRoot, int idata);

/**
 * @brief 二叉树遍历---------->前序遍历
 * 
 * @param iTreeRoot 指向根节点
 */
void PreOrderTraverse(BinaryTreePtr *iTreeRoot);

/**
 * @brief 二叉树遍历---------->中序遍历
 * 
 * @param iTreeRoot 指向根节点
 */
void InOrderTraverse(BinaryTreePtr *iTreeRoot);

/**
 * @brief 二叉树遍历---------->后序遍历
 * 
 * @param iTreeRoot 指向根节点
 */
void PostOrderTraverse(BinaryTreePtr *iTreeRoot);

/**
 * @brief 二叉树遍历---------->层次遍历
 * 
 * @param iTreeRoot 指向根节点
 */
void LayerOrderTraverse(BinaryTreePtr *iTreeRoot);

/**
 * @brief 二叉树测试接口
 * 
 */
void BinaryTree_FunctionTest(void);
#endif

#endif //CLION_ADT_TREE_H
