//
// Created by ASUS on 2022/5/9 0009.
//

#include "Function_Test.h"
static int Tower_of_Hanoi(int n,char x,char y,char z);
void Function_Test(void)
{
#if ADT_LIST_CLOSE
    printf("-------------ADT_List---------------\n");
    SequentialList_FunctionTest();
    CycleList_FunctionTest();
    MallocList_FunctionTest();
    StaticList_FunctionTest();
    DoubleList_FunctionTest();
#endif
    Stack_FunctionTest();
    char str1[]="abcdssss";char str2[]="cds";
    int re = match_string(str1, str2, 0);
    printf("re:%d\n",re);
    char str_T[20] = "aaaaaax";
    char str_S[20] = "aaaaaaaaaaacas";
    char T[20],S[20];
    memset(T,0, sizeof(T));
    memset(S,0, sizeof(S));
    T[0] = strlen(str_T);
    S[0] = strlen(str_S);
//    printf("str:%d\n",strlen(T));

    strcat(T,str_T);
    strcat(S,str_S);
//    printf("%d",T[0]);
    int next[10] = {0};
    Get_next(T,next);
    for(int i=0;i<10;i++)
    Get_nextval(T,next);
    for(int i=0;i<10;i++)
    printf("%d\t",next[i]);
//    Tower_of_Hanoi(4,'A','B','C');
    int index = Index_KMP(S,T,0);
    printf("index:%d\n",index);
#if USE_ADT_TREE_WAYS == BINARY_TREE
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
#endif
}

/*
 * 汉诺塔
 * **/
static int Tower_of_Hanoi(int n,char x,char y,char z)
{
    static int i = 0;
    if(n<2)
    {
        //将起始柱 x 移动到目标柱 z
        printf("%d:%c---->%c\n",++i,x,z);
    } else {
        //将起始柱 x 移动到辅助柱 y
        Tower_of_Hanoi(n-1,x,z,y);
        printf("%d:%c---->%c\n",++i,x,z);
        //将辅助柱 y 移动到目标柱 z
        Tower_of_Hanoi(n-1,y,x,z);
    }
}