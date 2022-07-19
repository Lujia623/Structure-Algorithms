//
// Created by Rougga on 2022/7/11 0011.
//

#include "ADT_Tree.h"

#if USE_ADT_TREE_WAYS == BINARY_TREE

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

void LayerOrderTraverse(BinaryTreePtr *iTreeRoot)
{
    if(NULL == (*iTreeRoot))
        return;
    //struct
}
#endif
