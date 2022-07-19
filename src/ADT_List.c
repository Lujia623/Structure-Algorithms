//
// Created by Rougga on 2022/4/16 0016.
//
#include "ADT_List.h"

#if USE_ADT_LIST_WAYS == USE_SEQUENTIAL_LIST

/*顺序表顺序存储*/
void CreatSequentialList(SqList *iList, int len)
{
    int i = 0;
    time_t _time;

    srand(time(&_time));
    memset(iList->data,0, sizeof(iList->data));
    for (i = 0; i < len; i++)
    {
        iList->data[i] = i;
        iList->length = len;
    }
}

bool SequentialListInsert(SqList* iList,int iPosition,int element)
{
    int i;

    if (SEQ_MAX_SIZE <= iPosition || 0 > iPosition)
    {
        printf("[%s]Insert ERROR\n", __FUNCTION__);
        return false;
    }

    for (i = iPosition; i < iList->length; i++)
    {
        iList->data[i] = iList->data[i + 1];
    }
    iList->length++;
    iList->data[iPosition - 1] = element;

    return true;
}

void ShowSequentialList(SqList* iList)
{
    int i = 0;

    while (i < iList->length)
    {
        printf("Sequential List data[%d]:\t%-10d\n", i, iList->data[i]);
        i++;
    }
}

void SequentialList_FunctionTest(void)
{
    SqList iList;
    CreatSequentialList(&iList,10);
    ShowSequentialList(&iList);
    printf("Insert\n");
    SequentialListInsert(&iList,5,555);
    ShowSequentialList(&iList);
}

#endif

#if USE_ADT_LIST_WAYS == USE_MALLOC_LIST

bool InitList(sList** iList)
{
///TODO：有问题的写法,待排查问题--------->已解决
    sList *newList = NULL;

    newList = (sList *) malloc(sizeof(sList));
    if (!newList)
    {
        memset(newList, 0, sizeof(sList));
        *iList = newList;
        return true;
    }
    return false;
}

//void InitList(sList *ilist)
//{
//    ilist->next =NULL;
//    ilist->num=1;
//}

void ListInsertHead(sList **iList, int iPosition, int element)
{
    sList *find_node = NULL, *new_node = NULL;
    int i = 1;

    if (!(*iList))
    {
        printf("List not init,then init List,\t%s\n",__FUNCTION__);
        InitList(iList);
    }

    find_node = *iList;

    while (find_node && i < iPosition)     //寻找第i个节点
    {
        find_node = find_node->next;
        i++;
    }

    if (!find_node || (i > iPosition))
    {
        printf("Insert ERROR,\t%s\n",__FUNCTION__);
        return;
    }
    new_node = (sList *) malloc(sizeof(sList));
    new_node->num = element;

    if ((*iList)->next)  //插入到第i个位置
    {
        printf("list not empty,insert %d position!!!\n",iPosition);
        new_node->next = find_node->next;
        find_node->next = new_node;
        (*iList)->num++;
    }
    else        //头插法(和头插法创建单链表相似)
    {
        printf("list is empty,Insert head!!!\n");
        new_node->next = (*iList)->next;
        (*iList)->next = new_node;
        (*iList)->num++;
    }
}

void CreateListHead(sList **iList, int num)
{
    int i = 0;
    time_t _time;
    sList *new_node = NULL;

    if(num <= 0)
    {
        printf("[%s]error,illegal list num:%d\n", __FUNCTION__, num);
        return;
    }

    srand(time(&_time));

    (*iList) = (sList *) malloc(sizeof(sList));
    memset(*iList, 0, sizeof(sList));
    (*iList)->num = num;

    for (i = 0; i < num; i++)
    {
        new_node = (sList *) malloc(sizeof(*new_node));
        memset(new_node, 0, sizeof(*new_node));
        new_node->num = rand() % 100 + 1;

        new_node->next = (*iList)->next;
        (*iList)->next = new_node;
    }

}

void CreateListTail(sList **iList,int num)
{
    int i=0;
    time_t _time;
    sList *new_node = NULL, *current_point = NULL;

    if(num <= 0)
    {
        printf("[%s]error,illegal list num:%d\n", __FUNCTION__, num);
        return;
    }

    srand(time(&_time));

    (*iList) = (sList *) malloc(sizeof(sList));
    memset(*iList, 0, sizeof(sList));
    (*iList)->num = num;
    current_point = (*iList);

    for(i=0;i<num;i++)
    {
        new_node = (sList *) malloc(sizeof(sList));
        memset(new_node, 0, sizeof(sList));
        new_node->num = rand() % 10;

        current_point->next = new_node;
        current_point = current_point->next;
    }
}

void ListInsertTail(sList **iList, int iPosition, int element)
{
    sList *find_node = NULL, *new_node = NULL;
    int i = 1;

    if (!(*iList))
    {
        printf("List not init,then init List,\t%s\n",__FUNCTION__);
        InitList(iList);
    }

    find_node = *iList;

    while (find_node && i < iPosition)     //寻找第i个节点
    {
        find_node = find_node->next;
        i++;
    }

    if (!find_node || (i > iPosition))
    {
        printf("Insert ERROR,\t%s\n",__FUNCTION__);
        return;
    }
    new_node = (sList *) malloc(sizeof(sList));
    new_node->next = NULL;
    new_node->num = element;

    if ((*iList)->next)  //插入到第i个位置
    {
        printf("list not empty,insert %d position!!!\n",iPosition);
        new_node->next = find_node->next;
        find_node->next = new_node;
        (*iList)->num++;
    }
    else        //尾插法(和尾插法创建单链表相似)
    {
        printf("list is empty,Insert tail!!!\n");
        (*iList)->next = new_node;
        (*iList)->num++;
    }
}

/**
 * 查找中间节点：时间复杂度O(n/2)
 * */
void SearchMidList(sList *iList,int *element)
{
    sList *current_node=NULL,*mid_node=NULL;

    current_node=mid_node=iList;

    while(NULL!=current_node->next)
    {
        if(NULL!=current_node->next->next)
        {
            current_node=current_node->next->next;
            mid_node=mid_node->next;
        } else
        {
            current_node=current_node->next;
        }
    }
    *element=mid_node->num;
}

sList *GetElement(sList *iList,int element)
{
    sList *current_point=NULL;

    current_point=iList->next;

    if(!current_point)
    {
        printf("list is empty,\t%s\n",__FUNCTION__);
        return NULL;
    }
    else
    {
        while (current_point)
        {
            if (current_point->num == element)
            {
                return current_point;
            }
            current_point = current_point->next;
        }
        return NULL;
    }
}
///TODO:待优化(此方法时间复杂度O(n),空间复杂度O(n))
sList *GetSameElement(sList *iList,int element)
{
    sList *current_point = NULL,*SaveElement_point=NULL;
    bool find_flag = false;

    current_point = iList->next;
    SaveElement_point=(sList*)malloc(sizeof(sList));
    memset(SaveElement_point,0, sizeof(sList));
    SaveElement_point->num = 1;
//    ListInsertTail(&SaveElement_point,SaveElement_point->num,element);

    if (!current_point)
    {
        printf("list is empty,\t%s\n",__FUNCTION__);
        return NULL;
    }
    else
    {
        while (current_point)
        {
            if (current_point->num == element)
            {
//                SaveElement_point=(sList*)malloc(sizeof(sList));
//                memset(SaveElement_point,0, sizeof(sList));
//                SaveElement_point->num++;
                ListInsertTail(&SaveElement_point,SaveElement_point->num,element);
                find_flag = true;
//                return current_point;
            }
            current_point = current_point->next;
        }
        if(!find_flag)
        {
            free(SaveElement_point);
            SaveElement_point = NULL;
        }
        return SaveElement_point;
    }
}

void ListDelete(sList **iList,int iPosition,int *element)
{
    sList *current_point = NULL, *temp_point = NULL;
    int i = 1;

    current_point = (*iList);

    while (current_point->next && i < iPosition)
    {
        current_point = current_point->next;
        i++;
    }

    if (!current_point->next && i > iPosition)
    {
        printf("delete error,\t%s\n",__FUNCTION__);
        return;
    }

    temp_point = current_point->next;
    current_point->next = temp_point->next;
    (*iList)->num--;

    *element = temp_point->num;
    free(temp_point);
    temp_point = NULL;
}

bool ClearList(sList **iList)
{
    sList *current_node = NULL, *next_node = NULL;

    if (!(*iList))
    {
        printf("iList is NULL already,\t%s\n",__FUNCTION__);
        return false;
    }
    else
    {
        current_node = (*iList)->next;
        while (current_node)
        {
            next_node = current_node->next;
            free(current_node);
//            memset(current_node, 0, sizeof(sList));    free之后不能对 free 指向的内容进行操作
            current_node = next_node;
        }
        memset(*iList,0, sizeof(sList));
        *iList = NULL;
    }
    return true;
}

void ShowList(sList **iList)
{
    sList *cur_node;

    cur_node = *iList;

    if (!cur_node)
    {
        printf("curent list is empty,\t%s\n",__FUNCTION__);
        return;
    }
    else
    {
        printf("list head addr:%p  list node num:%d\n", cur_node, cur_node->num);
        while (cur_node->next)
        {
            cur_node = cur_node->next;
            printf("list addr: %p,list data:%d\n", cur_node, cur_node->num);
        }
    }

}

sList *CreatNode(int value) {
    sList *list = NULL;
    list = (sList *) malloc(sizeof(sList));
    list->num = value;
    list->next = NULL;
    return list;
}

bool ListEmpty(sList *list) {
    sList *list_tmp = list;

    if (list_tmp->next) {
        return false;
    } else {
        return true;
    }
}

void MallocList_FunctionTest(void)
{
    sList *NewList1=NULL, *NewList2=NULL;
//    ShowList(&NewList1);
//    InitList(&NewList1);
//    ListInsertHead(&NewList1,1,300);
    ListInsertTail(&NewList1,1,0x12345678);
    ListInsertTail(&NewList1,1,123456);
//    printf("NewList1->list:%p,ele:%d\n",NewList1->next,((sList*)(NewList1->next))->num);
    ShowList(&NewList1);
    CreateListHead(&NewList2,10);
    ShowList(&NewList2);

    sList *NewList3=NULL;
//    InitList(&NewList3);
//    ListInsertTail(&NewList3,1,0x0F);
//    CreateListTail(&NewList3,10);
//    ShowList(&NewList3);
    int num;
    printf("delete after\n");
    ListDelete(&NewList2, 3, &num);
    ShowList(&NewList2);

    printf("clear after\n");
    ClearList(&NewList2);
    ShowList(&NewList2);
    ClearList(&NewList2);
    printf("NewList2:%p\n", NewList2);

    CreateListTail(&NewList1,20);
    ShowList(&NewList1);

    sList *l=GetElement(NewList1,3);
    printf("l:%p\n",l);
    printf("find same\n");
    sList *lsame=GetSameElement(NewList1,5);
    ShowList(&lsame);
    printf("find same:%p\n",lsame->next);
    int n;
    CreateListTail(&NewList3,20);
    printf("---------\n");
    ShowList(&NewList3);
    SearchMidList(NewList3,&n);
    printf("%d\n",n);
}

#endif

#if USE_ADT_LIST_WAYS == USE_CYCLE_LIST

static sList *head=NULL,*rear=NULL;

void InitCycleList(sList** iList)
{
    *iList = (sList *) malloc(sizeof(sList));
    memset(*iList, 0, sizeof(sList));
    (*iList)->num = rand() % 100;
    (*iList)->next = (*iList);
    rear = head = *iList;
}

int GetCycleListLength(sList* iList)
{
    int length = 0;
    sList *current_node = NULL;

    if (NULL == iList)
    {
        return length;
    } else
    {
        current_node = iList;
        do {
            current_node = current_node->next;
            length++;
        } while (current_node != iList);
        return length;
    }
}

void CycleListInsert(sList** iList,int iPosition,int element)
{
    int i;
    sList *current_node = NULL, *new_node = NULL;

    if (iPosition < 1 || iPosition > (GetCycleListLength(*iList) + 1))//插入位置不合理
    {
        printf("Insert ERROR,\t%s\n", __FUNCTION__);
        return;
    }

    if (!(*iList))//空表无法插入
    {
        printf("Insert ERROR,Cycle List is empty,\t%s\n", __FUNCTION__);
//        InitCycleList(iList);
        return;
    }
    else
    {
        i = 1;
        current_node = *iList;
        while (current_node->next != *iList && i < iPosition-1)//iPositon-1是防止插入位置是最后一个位置(和单链表不同之处在于没有头结点)
        {
            current_node = current_node->next;
            i++;//如插入第三个位置,当前的节点指针应该指向第二个位置
        }
        new_node = (sList *) malloc(sizeof(sList));
        memset(new_node, 0, sizeof(sList));
        new_node->num = element;

        if (1 == iPosition)//如果插入的位置刚好是第一个节点,将新的节点设置成为第一个节点
        {
            (*iList) = new_node;
        }

        new_node->next = current_node->next;
        current_node->next = new_node;
    }
}

void CycleListDelete(sList** iList,int iPosition,int* element)
{
    int i = 1;
    sList *current_node = NULL, *temp_point = NULL;

    if (1 > iPosition && iPosition > (GetCycleListLength(*iList) + 1)) {
        printf("Delete ERROR,\t%s\n", __FUNCTION__);
        return;
    }

    if (!(*iList)) {
        printf("Delete ERROR,Cycle List is empty,\t%s\n", __FUNCTION__);
        return;
    } else {
        current_node = *iList;
        while (current_node->next != *iList && i < iPosition - 1)
        {
            current_node = current_node->next;
            i++;
        }

        if (1 == GetCycleListLength(*iList) && 1 == iPosition)//删除的是第一个节点且循环链表中只有一个元素
        {
            free(*iList);//释放掉第一个节点的内存
            *iList = NULL;
        } else if (1 == iPosition)//删除的是第一个节点且循环链表中不止一个元素
        {
            while (current_node->next != (*iList)) {
                current_node = current_node->next;
            }
            current_node->next = (*iList)->next;
            temp_point = (*iList)->next;//保存要删除掉的节点指针
            free(*iList);//释放掉第一个节点的内存,free之后不能对(*iList)里面的内容进行操作
            (*iList) = temp_point;
            return;
        }

        temp_point = current_node->next;//保存要删除掉的节点指针
        current_node->next = current_node->next->next;
        free(temp_point);
        temp_point = NULL;
    }

}

void CreatCycleList(sList** iList,int num)
{
    time_t _time;
    sList *new_node = NULL, *current_node = NULL;

    if(num <= 0)
    {
        printf("[%s]error,illegal list num:%d\n", __FUNCTION__, num);
        return;
    }

    if (!(*iList))
    {
        printf("list is empty,then init list,\t%s\n", __FUNCTION__);
        InitCycleList(iList);
        if (num == GetCycleListLength(*iList))
            return;
    }

    srand(time(&_time));

    current_node = *iList;

    for (int i = 1; i < num; i++)
    {
        new_node = (sList *) malloc(sizeof(sList));
        memset(new_node, 0, sizeof(sList));
        new_node->num = rand() % 100;
        current_node->next = new_node;
        new_node->next = *iList;
        current_node = current_node->next;
        rear = new_node;
    }
}

void ShowCycleList(sList** iList)
{
    sList *current_node = NULL;

    if(*iList)
    {
        current_node = *iList;
        do
        {
            printf("Cycle list addr:%p,\tCycle list data:%-10d\n", current_node, current_node->num);
            current_node = current_node->next;
        }while(current_node != (*iList));
    }
    else
    {
        printf("[%s]error!\n",__FUNCTION__);
        return;
    }
}

void CycleList_FunctionTest(void)
{
    sList *NewList1=NULL,*NewList2=NULL;

//    InitCycleList(&NewList1);
    CreatCycleList(&NewList1,2);
    ShowCycleList(&NewList1);
    printf("insert\n");
    CycleListInsert(&NewList1,3,1111111);
    CycleListInsert(&NewList1,2,123456);
    CycleListInsert(&NewList1,2,222222);
    CycleListInsert(&NewList1,3,33333);
    CycleListInsert(&NewList1,5,5555);
    ShowCycleList(&NewList1);
    printf("delete\n");
    CycleListDelete(&NewList1,5,NULL);
    ShowCycleList(&NewList1);
    printf("cur num:%d\n",GetCycleListLength(NewList1));
    printf("card:\n\n\n");
    sList* current_node=NULL;
    CreatCycleList(&NewList2,13);
    current_node=NewList2;
    while(current_node->next!=NewList2)
    {
        current_node->num=0;
        current_node=current_node->next;
    }
    current_node->num=0;
    ShowCycleList(&NewList2);
    current_node=NewList2;
    current_node->num=1;
    for(int i=2;i<=13;++i)
    {
        int j=0;
            while(j<i)
            {
                current_node=current_node->next;
                if(0==current_node->num)
                {
                    ++j;
                }
            }
        current_node->num=i;
    }
    ShowCycleList(&NewList2);
}

#endif

#if USE_ADT_LIST_WAYS == USE_DOUBLE_LIST

static bool InitDoubleList(sDoubleList** iList)
{
    *iList=(sDoubleList*)malloc(sizeof(sDoubleList));
    memset(*iList,0, sizeof(sDoubleList));
    (*iList)->previous=(*iList);
    (*iList)->next=(*iList);
}

bool CreatDoubleList(sDoubleList** iList,int num)
{
    sDoubleList* current_node=NULL,*new_node=NULL;

    if(1>num)
    {
        printf("[%s]error,illegal list num:%d\n", __FUNCTION__, num);
        return false;
    }

    if(!(*iList))
    {
        printf("list is empty,then init list,\t%s\n", __FUNCTION__);
        InitDoubleList(iList);
        if(1==num)
            return true;
    }
    current_node=*iList;
    for(int i=1;i<num;i++)
    {
        new_node=(sDoubleList*)malloc(sizeof(sDoubleList));
        memset(new_node,0, sizeof(sDoubleList));
        current_node->next=new_node;
        new_node->previous=current_node;
        current_node=new_node;
    }
    current_node->next=(*iList);//新建的最后节点的next指向头节点
    (*iList)->previous=current_node;//头结点的previous指向最后节点
    return true;
}

int GetDoubleListLength(sDoubleList* iList)
{
    int length=0;
    sDoubleList* current_node=NULL;

    if(!(iList))
    {
        length=0;
    } else{
        current_node=iList;
        do{
            length++;
            current_node=current_node->next;
        }while(current_node!=iList);
    }
    return length;
}

bool DoubleListInsert(sDoubleList** iList,int iPosition,int element)
{
    int i;
    sDoubleList *current_node = NULL, *new_node = NULL;

    if (iPosition < 1 || iPosition > (GetDoubleListLength(*iList) + 1))//插入位置不合理
    {
        printf("Insert ERROR,\t%s\n", __FUNCTION__);
        return false;
    }

    if (!(*iList))//空表无法插入
    {
        printf("Insert ERROR,Cycle List is empty,\t%s\n", __FUNCTION__);
//        InitCycleList(iList);
        return false;
    }
    else
    {
        i = 1;
        current_node = *iList;
        while (current_node->next != *iList && i < iPosition-1)//iPositon-1是防止插入位置是最后一个位置(和单链表不同之处在于没有头结点)
        {
            current_node = current_node->next;
            i++;//如插入第三个位置,当前的节点指针应该指向第二个位置
        }
        new_node = (sDoubleList *) malloc(sizeof(sDoubleList));
        memset(new_node, 0, sizeof(sDoubleList));
        new_node->data = element;

        if (1 == iPosition)//如果插入的位置刚好是第一个节点,将新的节点设置成为第一个节点
        {
            (*iList) = new_node;
        }
        //先处理后面的节点
        new_node->next = current_node->next;
        current_node->next->previous=new_node;
        //再处理curent_node节点
        new_node->previous=current_node;
        current_node->next=new_node;

        return true;
    }
}

bool DoubleListDelete(sDoubleList** iList,int iPosition,int* element)
{
    int i = 1;
    sDoubleList *current_node = NULL, *temp_point = NULL;

    if (1 > iPosition && iPosition > (GetDoubleListLength(*iList) + 1)) {
        printf("Delete ERROR,\t%s\n", __FUNCTION__);
        return false;
    }

    if (!(*iList)) {
        printf("Delete ERROR,Cycle List is empty,\t%s\n", __FUNCTION__);
        return false;
    } else {
        current_node = *iList;
        while (current_node->next != *iList && i < iPosition - 1)
        {
            current_node = current_node->next;
            i++;
        }

        if (1 == GetDoubleListLength(*iList) && 1 == iPosition)//删除的是第一个节点且循环链表中只有一个元素
        {
            free(*iList);//释放掉第一个节点的内存
            *iList = NULL;
        } else if (1 == iPosition)//删除的是第一个节点且循环链表中不止一个元素
        {
            while (current_node->next != (*iList)) {
                current_node = current_node->next;
            }
            current_node->next = (*iList)->next;
            temp_point = (*iList)->next;//保存要删除掉的节点指针
            free(*iList);//释放掉第一个节点的内存,free之后不能对(*iList)里面的内容进行操作
            (*iList) = temp_point;

            return true;
        }

        temp_point = current_node->next;//保存要删除掉的节点指针
        current_node->next = current_node->next->next;
        free(temp_point);
        temp_point = NULL;

        return true;
    }
}

void ClearDoubleList(sDoubleList** iList)
{
    int i=0;
    sDoubleList* current_node=NULL,*temp_node;

    if((!*iList))
    {
        printf("[%s]Clear ERROR!\n",__FUNCTION__);
        return;
    }
    current_node=*iList;
    i=GetDoubleListLength(*iList);
    while(i--)
    {
        temp_node=current_node->next;
        free(current_node);
        current_node=temp_node;
    }
    *iList=NULL;//全部释放完，指向空
}

void ShowDoubleList(sDoubleList** iList)
{
    sDoubleList* current_node=NULL;

    if(*iList)
    {
        current_node = *iList;
        do
        {
            printf("Double list addr:%p,data:%d,\tnext:%p,previous:%p\n", current_node, current_node->data,current_node->next,current_node->previous);
            current_node = current_node->next;
        }while(current_node != (*iList));
    }
    else
    {
        printf("[%s]error!\n",__FUNCTION__);
        return;
    }
}

void DoubleList_FunctionTest(void)
{
    sDoubleList* NewList1=NULL;

    CreatDoubleList(&NewList1,5);
    ShowDoubleList(&NewList1);
    printf("\n\n");
    DoubleListInsert(&NewList1,2,123);
    DoubleListInsert(&NewList1,1,111);
    DoubleListDelete(&NewList1,1,NULL);
    ShowDoubleList(&NewList1);
    printf("clear\n");
    ClearDoubleList(&NewList1);
    ShowDoubleList(&NewList1);
}

#endif

#if USE_ADT_LIST_WAYS == USE_STATIC_LIST

void InitStaticLinkList(StaticLinkList space)
{
    int i = 0;

    memset(space, 0, sizeof(StaticLinkList));

    for (i = 0; i < STATIC_MAX_SIZE - 1; i++)
    {
        space[i].cursor = i + 1;
    }
    space[STATIC_MAX_SIZE - 1].cursor = 0;
}

void CreatStaticList(StaticLinkList space, int num)
{
    int i;
    int Idle_index;
    time_t _time;

    if (num < 1 || num >= STATIC_MAX_SIZE)
    {
        printf("the num(%d),error!!!\n", num);
        return;
    }

    srand(time(&_time));

    for (i = 0; i < num; ++i)
    {
        Idle_index = GetIdleIndex(space);
        space[Idle_index].data = rand() % 20;
    }

    space[STATIC_MAX_SIZE - 1].cursor = 1;//最后的index中游标保存头结点的index
    space[i].cursor = 0;//无数据的元素让其游标为0
}

int GetIdleIndex(StaticLinkList space)
{
    int Idle_index;

    Idle_index = space[0].cursor;
    if (space[0].cursor) //index=0的游标保存备用链表的下标
    {
        space[0].cursor = space[Idle_index].cursor; //每次从备用链表中获取空间，更新index=0处的游标值
    }
    return Idle_index;
}

int GetStaticListLength(StaticLinkList space)
{
    int length = 0;
    int curent_index;

    curent_index = space[STATIC_MAX_SIZE - 1].cursor;

    while (curent_index)
    {
        curent_index = space[curent_index].cursor;
        length++;
    }
    return length;
}

static void FreeStaticList(StaticLinkList space,int iPosition)
{
    space[iPosition].cursor = space[0].cursor;//将删除的静态链表的节点链接到备用链表上
    space[0].cursor = iPosition;//更新备用链表头结点
}

void InsertStaticList(StaticLinkList space,int iPosition,int element)
{
    int i;
    int Idle_index, curent_index;

    if (iPosition < 1 || iPosition > (GetStaticListLength(space) + 1))
    {
        printf("insert %d error,%s\n", iPosition, __FUNCTION__);
        return;
    }

    curent_index = STATIC_MAX_SIZE - 1;
    Idle_index = GetIdleIndex(space);

    if(Idle_index)
    {
        for (i = 1; i < iPosition; i++)
        {
            curent_index = space[curent_index].cursor;
        }

        space[Idle_index].cursor = space[curent_index].cursor;
        space[curent_index].cursor = Idle_index;
        space[Idle_index].data = element;
    }
}

void DeleteStaticList(StaticLinkList space,int iPosition)
{
    int i;
    int curent_index;

    if (iPosition < 1 || iPosition >= GetStaticListLength(space))
    {
        printf("delete %d error,%s\n", iPosition, __FUNCTION__);
        return;
    }

    curent_index = STATIC_MAX_SIZE - 1;

    for (i = 1; i < iPosition; i++)
    {
        curent_index = space[curent_index].cursor;
    }

    space[curent_index].cursor = space[space[curent_index].cursor].cursor;//将要删除节点的后面一个节点的游标赋值给当前节点游标
    FreeStaticList(space, iPosition);
}

void ShowStaticList(StaticLinkList space)
{
    int curent_cursor = 0;
    int i = 1;

    if (space[STATIC_MAX_SIZE - 1].cursor)//静态链表不为空
    {
        curent_cursor = space[STATIC_MAX_SIZE - 1].cursor;
        while (curent_cursor)
        {
            printf("StaticLinkList [%d],data:%-10d\t----->cursor:%d\n", curent_cursor, space[curent_cursor].data, space[curent_cursor].cursor);
            curent_cursor = space[curent_cursor].cursor;//获取当前index的游标
        }
    }
    else
    {
        printf("StaticLinkList is NULL\n");
        return;
    }
}

void StaticList_FunctionTest(void)
{
    StaticLinkList staticLink;

    InitStaticLinkList(staticLink);
    CreatStaticList(staticLink,1);
    ShowStaticList(staticLink);
    printf("insert\n");
    InsertStaticList(staticLink,6,123456789);
    ShowStaticList(staticLink);
    printf("delete\n");
    DeleteStaticList(staticLink,2);
    ShowStaticList(staticLink);
    printf("insert\n");
    InsertStaticList(staticLink,3,123456);
    ShowStaticList(staticLink);
}

#endif