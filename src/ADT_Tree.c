//
// Created by Rougga on 2022/7/11 0011.
//

#include "ADT_Tree.h"

#if USE_ADT_TREE_WAYS & BINARY_TREE

void InsertTree(BinaryTreePtr *iTreeRoot, int idata)
{
    BinaryTreeNode *new_node = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
    new_node->data = idata;
    new_node->left_node = NULL;
    new_node->right_node = NULL;

    if (NULL == *iTreeRoot) {               //根节点为 NULL,新的节点为根节点
        *iTreeRoot = new_node;
    } else {
        BinaryTreePtr current_node = *iTreeRoot;
        while (NULL != current_node) {                           //根节点不为 NULL,需要遍历,小的在左树,大的在右树
            if (idata < current_node->data) {
                if (NULL == current_node->left_node) {          //判断左孩子是否为 NULL,为 NULL说明查找到插入位置,否则继续遍历
                    current_node->left_node = new_node;
                    return;
                } else {
                    current_node = current_node->left_node;
                }
            } else {
                if (NULL == current_node->right_node) {         //判断左孩子是否为 NULL,为 NULL说明查找到插入位置,否则继续遍历
                    current_node->right_node = new_node;
                    return;
                } else {
                    current_node = current_node->right_node;
                }
            }
        }
    }
}

void PreOrderTraverse(BinaryTreePtr *iTreeRoot)
{
    if (NULL == *iTreeRoot)
        return;
    printf("%d\n", (*iTreeRoot)->data);
    PreOrderTraverse(&(*iTreeRoot)->left_node);
    PreOrderTraverse(&(*iTreeRoot)->right_node);
}

void InOrderTraverse(BinaryTreePtr *iTreeRoot)
{
    if (NULL == *iTreeRoot)
        return;
    InOrderTraverse(&(*iTreeRoot)->left_node);
    printf("%d\n", (*iTreeRoot)->data);
    InOrderTraverse(&(*iTreeRoot)->right_node);
}

void PostOrderTraverse(BinaryTreePtr *iTreeRoot)
{
    if(NULL == (*iTreeRoot))
        return;
    PostOrderTraverse(&(*iTreeRoot)->left_node);
    PostOrderTraverse(&(*iTreeRoot)->right_node);
    printf("%d\n", (*iTreeRoot)->data);
}

/**
 * @brief 初始化队列
 * 
 * @param iTreeQueue 入队出队指针架构
 */
static void InitTreeQueue(sTreeLinkQueue *iTreeQueue)
{
    iTreeQueue->fifo_in = iTreeQueue->fifo_out = NULL;
}

/**
 * @brief 
 * 
 * @param iTreeQueue 入队出队指针架构
 * @return true 队列为空
 * @return false 队列非空
 */
static bool isTreeQueueEmpty(sTreeLinkQueue *iTreeQueue)
{
    return (iTreeQueue->fifo_out == NULL ? true : false);
}

/**
 * @brief 入队列(循环队列,队列节点采用循环单向链表的形式)
 * 
 * @param iTreeQueue 入队出队指针架构
 * @param iTreeNode 入队二叉树节点
 */
static void PushTreeQueue(sTreeLinkQueue *iTreeQueue,BinaryTreeNode iTreeNode)
{
    sTreeQueueNode *new_node = NULL;

    new_node = (sTreeQueueNode *) malloc(sizeof(sTreeQueueNode));
    if (NULL == new_node) {
        printf("%s in %d malloc failed!\n", __FUNCTION__, __LINE__);
        return;
    }
    memset(new_node, 0, sizeof(sTreeQueueNode));

    if (isTreeQueueEmpty(iTreeQueue)) {
        new_node->next = new_node;
        iTreeQueue->fifo_out = iTreeQueue->fifo_in = new_node;
    } else {
        new_node->next = iTreeQueue->fifo_in->next;
        iTreeQueue->fifo_in->next = new_node;
        iTreeQueue->fifo_in = new_node;
    }
    new_node->treeNode = iTreeNode;
}

/**
 * @brief 出队列
 * 
 * @param iTreeQueue 入队出队指针架构
 */
static void PopTreeQueue(sTreeLinkQueue *iTreeQueue)
{
    sTreeQueueNode *delete_node = NULL;

    if (isTreeQueueEmpty(iTreeQueue)) {
        printf("%s ERROR!\n", __FUNCTION__);
        return;
    }

    if (iTreeQueue->fifo_in->next == iTreeQueue->fifo_out->next) {   //当只有一个节点时,pop后需要改变指向,赋值为 NULL
        free(iTreeQueue->fifo_out);
        iTreeQueue->fifo_out = iTreeQueue->fifo_in = NULL;
    } else {
        delete_node = iTreeQueue->fifo_out->next;
        iTreeQueue->fifo_in->next = iTreeQueue->fifo_out->next;
        free(iTreeQueue->fifo_out);
        iTreeQueue->fifo_out = delete_node;
    }
}

/**
 * @brief Get the Tree Head object
 * 
 * @param iTreeQueue 入队出队指针架构
 * @return sTreeQueueNode* 出队队列树指针
 */
static sTreeQueueNode *GetTreeHead(sTreeLinkQueue *iTreeQueue)
{
    if (isTreeQueueEmpty(iTreeQueue)) {
        printf("%s ERROR!\n", __FUNCTION__);
        return NULL;
    }
    return iTreeQueue->fifo_out;
}

void LayerOrderTraverse(BinaryTreePtr *iTreeRoot)
{
    sTreeLinkQueue treeNodeLink;
    sTreeQueueNode *TreeHeadNode = NULL;

    if (NULL == (*iTreeRoot))
        return;
    InitTreeQueue(&treeNodeLink);
    PushTreeQueue(&treeNodeLink, **iTreeRoot);

    while (!isTreeQueueEmpty(&treeNodeLink)) {
        TreeHeadNode = GetTreeHead(&treeNodeLink);                      //先获取队列 Head元素
        BinaryTreeNode TreeNode = TreeHeadNode->treeNode;
        printf("%d\n", TreeHeadNode->treeNode.data);
        PopTreeQueue(&treeNodeLink);                                    //出队列
        if (TreeNode.left_node) {                                   //左子树节点不为空则入队列
            PushTreeQueue(&treeNodeLink, *TreeNode.left_node);
        }
        if (TreeNode.right_node) {                                   //右子树节点不为空则入队列a
            PushTreeQueue(&treeNodeLink, *TreeNode.right_node);
        }
    }
}

void BinaryTree_FunctionTest(void)
{
    BinaryTreePtr root = NULL;
    time_t _time = 0;
    srand(time(NULL));
    for (uint8_t i = 0; i < 10; i++) {
        InsertTree(&root, (int)(rand()%10));
    }
    printf("PreOrderTraverse:\n");
    PreOrderTraverse(&root);
    printf("InOrderTraverse:\n");
    InOrderTraverse(&root);
    printf("PostOrderTraverse:\n");
    PostOrderTraverse(&root);
    printf("LayerOrderTraverse:\n");
    LayerOrderTraverse(&root);
}
#endif
