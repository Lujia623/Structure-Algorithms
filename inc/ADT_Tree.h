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

#define ADT_TREE_CLOSE                  BIT(0)           //关闭所有
#define PARENTS_CHILDS_WAYS             BIT(1)          //数的双亲表示法
#define BINARY_TREE                     BIT(2)          //二叉树
#define THREADED_BINARY_TREE            BIT(3)          //线索二叉树

#define USE_ADT_TREE_WAYS    (PARENTS_CHILDS_WAYS | BINARY_TREE |THREADED_BINARY_TREE)
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
#endif /*PARENTS_CHILDS_WAYS*/

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

/**
 * @brief 使用递归方式删除二叉树并释放空间(方式类似于后续遍历)
 * 
 * @param iTreeRoot 指向根节点
 */
void BinaryTree_delete(BinaryTreePtr *iTreeRoot);
#endif /*USE_ADT_TREE_WAYS & BINARY_TREE*/

#if USE_ADT_TREE_WAYS & THREADED_BINARY_TREE
typedef enum pointTag {
    LINK,               //表示左右孩子
    THREAD              //表示前驱后继节点
} ePointerTag;

typedef struct ThreadedBinaryTree_Node {
    ElemType data;                                                       //线索二叉树数据域
    struct ThreadedBinaryTree_Node *left_node,*right_node;              //线索二叉树左右孩子节点
    ePointerTag left_tag;
    ePointerTag right_tag;
} sThreadedBinaryTree_Node, *sThreadedBinaryTreePtr;

/**
 * @brief 前序遍历创建二叉树
 * 
 * @param iTreeRoot 二叉树线索化结构
 * @param value 二叉树节点数据域值
 */
void ThreadBinaryTree_Init(sThreadedBinaryTreePtr *iTreeRoot, int *value);

/**
 * @brief 二叉树线索化,中序遍历(第一个节点的前驱节点和最后一个节点的后继节点指向NULL)
 * 
 * @param iTreeRoot 二叉树线索化结构
 */
void InThreadedBinaryTree(sThreadedBinaryTreePtr *iTreeRoot);

/**
 * @brief 二叉树线索化,中序遍历(第一个节点的前驱节点和最后一个节点的后继节点指向根节点(*iTreeRoot))
 * 
 * @param iTreeRoot 二叉树线索化结构
 * @param head_node 头结点
 */
void InThreadedBinaryTreeThreading(sThreadedBinaryTreePtr *iTreeRoot, sThreadedBinaryTreePtr *head_node);

/**
 * @brief 循环遍历
 * 
 * @param head_node 线索二叉树头结点
 */
void InOrderTraverse_Thread(sThreadedBinaryTreePtr *head_node);

/**
 * @brief Get the Precursor Node object(查找当前节点的前驱节点)
 * 
 * @param iTreeRoot 要查找的节点
 * @return sThreadedBinaryTreePtr 返回当前节点的前驱节点
 */
sThreadedBinaryTreePtr getPrecursorNode(sThreadedBinaryTreePtr iTreeRoot);

/**
 * @brief Get the Successor Node object(查找当前节点的后继节点)
 * 
 * @param iTreeRoot 要查找的节点
 * @return sThreadedBinaryTreePtr 返回当前节点的后继节点
 */
sThreadedBinaryTreePtr getSuccessorNode(sThreadedBinaryTreePtr iTreeRoot);

/**
 * @brief 判定当前节点左域是否指向前驱
 * 
 * @param iTreeRoot 二叉树线索化结构
 * @return true 当前节点的左域指向前驱
 * @return false 当前节点的左域指向左孩子
 */
bool isPrecursorNode(sThreadedBinaryTreePtr iTreeRoot);

/**
 * @brief 判定当前节点右域是否指向后继
 * 
 * @param iTreeRoot 二叉树线索化结构
 * @return true 当前节点的右域指向后继
 * @return false 当前节点的右域指向右孩子
 */
bool isSuccessorNode(sThreadedBinaryTreePtr iTreeRoot);

/**
 * @brief 采用后序遍历方式删除线索二叉树(和InThreadedBinaryTree接口联合使用,若是含有头结点不会删除头结点)
 * 
 * @param iTreeRoot 线索二叉树的根节点
 */
void ThreadedBinaryTree_delete(sThreadedBinaryTreePtr *iTreeRoot);

/**
 * @brief 采用循环遍历的方式删除二叉树(和InThreadedBinaryTreeThreading接口联合使用,会删除头结点)
 * 
 * @param head_node 线索二叉树的头节点
 */
void ThreadBinaryTree_destroy(sThreadedBinaryTreePtr *head_node);

#endif /*USE_ADT_TREE_WAYS & THREADED_BINARY_TREE*/

#endif //CLION_ADT_TREE_H
