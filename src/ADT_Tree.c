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

void BinaryTree_delete(BinaryTreePtr *iTreeRoot)
{
    if ((*iTreeRoot)->left_node != NULL) {
        BinaryTree_delete(&(*iTreeRoot)->left_node);
    }
    if ((*iTreeRoot)->right_node != NULL) {
        BinaryTree_delete(&(*iTreeRoot)->right_node);
    }
    free(*iTreeRoot);
    *iTreeRoot = NULL;
}

#endif /*USE_ADT_TREE_WAYS & BINARY_TREE*/

#if USE_ADT_TREE_WAYS & THREADED_BINARY_TREE

static sThreadedBinaryTreePtr Precursor_Node = NULL;

void ThreadBinaryTree_Init(sThreadedBinaryTreePtr *iTreeRoot, int *value)
{
    sThreadedBinaryTree_Node *new_node = NULL;
    static int index = 0;

    if (*(value + index) == '#') {
        *iTreeRoot = NULL;
        index++;
        return;
    } else {
        new_node = (sThreadedBinaryTree_Node *) malloc(sizeof(sThreadedBinaryTree_Node));
        new_node->left_node = new_node->right_node = NULL;
        new_node->left_tag = new_node->right_tag = LINK;
        new_node->data = *(value + index);
        (*iTreeRoot) = new_node;
        index++;

        ThreadBinaryTree_Init(&(*iTreeRoot)->left_node, value);
        ThreadBinaryTree_Init(&(*iTreeRoot)->right_node, value);
    }
}

void InThreadedBinaryTree(sThreadedBinaryTreePtr *iTreeRoot)
{

    if (NULL == (*iTreeRoot)) {
        return;
    }

    InThreadedBinaryTree(&(*iTreeRoot)->left_node);

    if ((*iTreeRoot)->left_node == NULL) {
        (*iTreeRoot)->left_tag = THREAD;
        (*iTreeRoot)->left_node = Precursor_Node;
    }

    if ((Precursor_Node != NULL) && (Precursor_Node->right_node == NULL)) {     //这两句判断不能反,只有当前节点不为NULL时才能去访问它的域
        Precursor_Node->right_tag = THREAD;             //后继节点标志
        Precursor_Node->right_node = (*iTreeRoot);      //将上一个节点的右指针指向当前节点,完成上一个访问过的节点后继节点的赋值
    }

    Precursor_Node = (*iTreeRoot);          //改变指针指向,永远指向的是刚才访问过的节点

    InThreadedBinaryTree(&(*iTreeRoot)->right_node);
}

void InThreadedBinaryTreeThreading(sThreadedBinaryTreePtr *iTreeRoot, sThreadedBinaryTreePtr *head_node)
{
    *head_node = (sThreadedBinaryTree_Node*)malloc(sizeof(sThreadedBinaryTree_Node));
    /**
     * 创建一个头结点,方便循环遍历
    */
    (*head_node)->left_tag = LINK;
    (*head_node)->right_tag = THREAD;
    (*head_node)->left_node = (*iTreeRoot);
    (*head_node)->right_node = (*head_node);
    Precursor_Node = *iTreeRoot;
    InThreadedBinaryTree(iTreeRoot);
    Precursor_Node->right_tag = THREAD;
    Precursor_Node->right_node = *iTreeRoot;
    (*head_node)->right_node = Precursor_Node;
}

void InOrderTraverse_Thread(sThreadedBinaryTreePtr *head_node)
{
    sThreadedBinaryTree_Node *current_node = NULL;

    current_node = (*head_node)->left_node;

    while (current_node != (*head_node)->right_node) {

        while (current_node->left_tag == LINK) {            //存在左子树则遍历
            current_node = current_node->left_node;
        }

        printf("%d\n", current_node->data);

        while (current_node->right_tag == THREAD) {          //当前节点存在后继则遍历后继节点
            current_node = current_node->right_node;
            printf("%d\n", current_node->data);
        }
        current_node = current_node->right_node;            //current_node指向右子树

        /**
         * 如果线索化之后最后一个节点指向树根节点,需要遍历最后一个节点;
         * 如果最后一个节点指向头结点,则不需要加最后节点的遍历;
         * 
         */

        if (current_node == (*head_node)->right_node) {
            printf("%d\n", current_node->data);
        }
    }
}

sThreadedBinaryTreePtr getPrecursorNode(sThreadedBinaryTreePtr iTreeRoot)
{
    sThreadedBinaryTreePtr current_node = NULL;

    if(iTreeRoot == NULL) {
        printf("%s ERROR\n", __FUNCTION__);
        return NULL;
    }

    if(iTreeRoot->left_tag == THREAD) {
        return iTreeRoot->left_node;
    }

    current_node = iTreeRoot->left_node;
    while (current_node->right_tag == LINK) {
        current_node = current_node->left_node;
    }
    return current_node;
}

sThreadedBinaryTreePtr getSuccessorNode(sThreadedBinaryTreePtr iTreeRoot)
{
    sThreadedBinaryTreePtr current_node = NULL;

    if(iTreeRoot == NULL) {
        printf("%s ERROR\n", __FUNCTION__);
        return NULL;
    }

    if(iTreeRoot->right_tag == THREAD) {
        return iTreeRoot->right_node;
    }

    current_node = iTreeRoot->right_node;
    while (current_node->left_tag == LINK) {
        current_node = current_node->right_node;
    }
    return current_node;
}

bool isPrecursorNode(sThreadedBinaryTreePtr iTreeRoot)
{
    if(iTreeRoot == NULL) {
        printf("%s ERROR!\n", __FUNCTION__);
        return false;
    }
    return (iTreeRoot->left_tag == THREAD);
}

bool isSuccessorNode(sThreadedBinaryTreePtr iTreeRoot)
{
    if(iTreeRoot == NULL) {
        printf("%s ERROR!\n", __FUNCTION__);
        return false;
    }
    return (iTreeRoot->right_tag == THREAD);
}

void ThreadedBinaryTree_delete(sThreadedBinaryTreePtr *iTreeRoot)
{
    if((*iTreeRoot)->left_node != (*iTreeRoot) && (*iTreeRoot)->left_tag == LINK) {
        ThreadedBinaryTree_delete(&(*iTreeRoot)->left_node);
    }
    if((*iTreeRoot)->right_node != (*iTreeRoot) && (*iTreeRoot)->right_tag == LINK) {
        ThreadedBinaryTree_delete(&(*iTreeRoot)->right_node);
    }
    free(*iTreeRoot);
    *iTreeRoot = NULL;
}

void ThreadBinaryTree_destroy(sThreadedBinaryTreePtr *head_node)
{
    sThreadedBinaryTreePtr delete_node = NULL, temp_point = NULL;

    delete_node = (*head_node)->left_node;

    while (delete_node != NULL) {
        while (delete_node->left_tag == LINK) {
            delete_node = delete_node->left_node;
        }
        while (delete_node->right_tag == THREAD) {
            temp_point = delete_node->right_node;
            free(delete_node);
            delete_node = temp_point;
        }
        temp_point = delete_node->right_node;
        free(delete_node);
        delete_node = temp_point;
        if (delete_node == (*head_node)->right_node) {
            free(delete_node);
            delete_node = NULL;
        }
    }
    free(*head_node);
    *head_node = NULL;
}
#endif /*USE_ADT_TREE_WAYS & THREADED_BINARY_TREE*/

void BinaryTree_FunctionTest(void)
{
    BinaryTreePtr root = NULL;
    sThreadedBinaryTreePtr threadRoot = NULL, head_node = NULL;
    int _value[] = {59, 6, 4, '#', '#', 26, 25, 16, 9, '#', '#', '#', '#', 37, '#', '#', 89, '#', 97, '#', '#'}; //前序遍历

    time_t _time = 0;
    srand(time(NULL));
    for (uint8_t i = 0; i < 10; i++) {
        InsertTree(&root, (int)(rand()%100));
    }
    printf("PreOrderTraverse:\n");
    PreOrderTraverse(&root);
    printf("InOrderTraverse:\n");
    InOrderTraverse(&root);
    printf("PostOrderTraverse:\n");
    PostOrderTraverse(&root);
    printf("LayerOrderTraverse:\n");
    LayerOrderTraverse(&root);
    BinaryTree_delete(&root);
    printf("ThreadBinaryTree_Init:\n");
    ThreadBinaryTree_Init(&threadRoot, _value);
    InThreadedBinaryTreeThreading(&threadRoot, &head_node);
    InOrderTraverse_Thread(&head_node);
    ThreadBinaryTree_destroy(&head_node);
}
