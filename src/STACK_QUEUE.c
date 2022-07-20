//
// Created by ASUS on 2022/5/9 0009.
//

#include "STACK_QUEUE.h"

typedef enum{
    OTC = 3,
    HEX,
}eScale;

static void BintoHexOrOct(eScale type);
static void infixToSuffix(char *des, const char *src);

#if USE_STACK_WAY == USE_SEQUENTIAL_STACK
bool InitStack(sStack* iStack)
{
    if (-1 != iStack->top)
    {
        iStack->top = -1;
        memset(iStack->data, 0, sizeof(iStack->data));
        return true;
    }
    else
    {
        return false;
    }
}

bool push(sStack* iStack,ElemType element)
{
    if ((STACK_MAX_SIZE - 1) == iStack->top)
        return false;

    iStack->top++;
    iStack->data[iStack->top] = element;
    return true;
}

bool pop(sStack* iStack,ElemType* element)
{
    if (-1 == iStack->top)
        return false;

    *element = iStack->data[iStack->top];
    iStack->top--;
    return true;
}

int StackLength(sStack iStack)
{
    return (iStack.top - (-1));
}

void ClearStack(sStack iStack)
{
    iStack.top = -1;
}

#elif USE_STACK_WAY == USE_MOLLOC_STACK
bool InitStack(SqStack *iStack)
{
    iStack->bottom = (int *) malloc(STACK_MAX_SIZE * sizeof(int));
    if (!iStack->bottom)
        return false;
    iStack->top = iStack->bottom;
    iStack->stack_length = STACK_MAX_SIZE;
    return true;
}

bool push(SqStack *iStack, ElemType element)
{
    if ((iStack->top - iStack->bottom) >= iStack->stack_length)
        return false;
    *(iStack->top) = element;
    iStack->top++;
    return true;
}

bool pop(SqStack *iStack, ElemType *element)
{
    if (iStack->top == iStack->bottom)
        return false;
    *element = *(--iStack->top);
    return true;
}

int StackLength(SqStack iStack)
{
    if (iStack.top && iStack.bottom)
        return (iStack.top - iStack.bottom);
    else
        printf("[%s]ERROR,line:%d !!!\n", __FUNCTION__, __LINE__);
    return 0;
}

bool Stack_is_Empty(SqStack iStack)
{
    return (iStack.top == iStack.bottom);
}

int GetTop(SqStack iStack)
{
    if (Stack_is_Empty(iStack))
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return -1;
    }
    return *(--iStack.top);
}

void ClearStack(SqStack *iStack)
{
    iStack->top = iStack->bottom;
}

void DestroyStack(SqStack* iStack)
{
    if (iStack->bottom)
        free(iStack->bottom);

    iStack->bottom = iStack->top = NULL;
    iStack->stack_length = 0;
}

#elif USE_STACK_WAY == USE_LIST_STACK
bool InitStack(sLinkStack* iLinkStack)
{
    iLinkStack->top = NULL;
    iLinkStack->length = 0;
    return true;
}

bool push(sLinkStack* iLinkStack,ElemType element)
{
    sStackNode *new_node;
    new_node = (sStackNode *) malloc(sizeof(sStackNode));
    new_node->data = element;
    new_node->next = iLinkStack->top;
    iLinkStack->top = new_node;
    iLinkStack->length++;
    return true;
}

bool pop(sLinkStack* iLinkStack,ElemType* element)
{
    sStackNode* pop_node=NULL;

    if(0==iLinkStack->length)
        return false;
    *element=iLinkStack->top->data;
    pop_node=iLinkStack->top;
    iLinkStack->top=iLinkStack->top->next;
    free(pop_node);
    iLinkStack->length--;
    return true;
}

int StackLength(sLinkStack iLinkStack)
{
    return iLinkStack.length;
}

bool Stack_is_Empty(sLinkStack iLinkStack)
{
    return (0==iLinkStack.length);
}

void DestroyStack(sLinkStack* iLinkStack)
{
    sStackNode* current_node=NULL;

    if(!iLinkStack->top)
    {
        printf("[%s]ERROR\n",__FUNCTION__);
        return;
    }
    else
    {
        while(iLinkStack->length)
        {
            current_node=iLinkStack->top;
            iLinkStack->top=iLinkStack->top->next;
            free(current_node);
            iLinkStack->length--;
        }
    }
}

int GetTop(sLinkStack iLinkStack)
{
    if(Stack_is_Empty(iLinkStack))
    {
        printf("[%s]ERROR\n",__FUNCTION__);
        return -1;
    }
    else
    {
        return iLinkStack.top->data;
    }
}
#endif

#if USE_STACK_WAY == USE_MOLLOC_STACK
/*
 * 二进制转8或者6进制
 * */
static void BintoHexOrOct(eScale type)
{
    SqStack stack3;
    SqStack stack4;
    InitStack(&stack3);
    InitStack(&stack4);
    int num = 0, len;

    char c;
    scanf("%c", &c);
    while ('#' != c) {
        push(&stack3, c - 48);
        scanf("%c", &c);
    }
    getchar();
    int bin;
    int i = 0;
    printf("len:%d\n", StackLength(stack3));
    len = StackLength(stack3);
    while (i < len)
    {
        num = 0;
        if (StackLength(stack3) >= type)
        {
            for (int j = 0; j < type; j++)
            {
                pop(&stack3, &bin);
                num = num + bin * pow(2, j);
            }
        }
        else
        {
            for (int j = 0; !Stack_is_Empty(stack3); j++)
            {
                pop(&stack3, &bin);
                num = num + bin * pow(2, j);
            }
        }
        push(&stack4, num);
        i += type;
    }
    len = StackLength(stack4);
    int o;
    for (int i = 0; i < len; i++)
    {
        pop(&stack4, &o);
        if (o > 9)
            printf("%c", 'a' + (o - 10));
        else
            printf("%d", o);
    }
    printf("\n");
}
/**
 * 逆波兰算法
 * */
static bool ISTOP(char src_symbol,char top_symbol)
{
    if ('(' == top_symbol)
        return false;
    if ('*' == src_symbol || '/' == src_symbol)
    {
        if ('+' == top_symbol || '-' == top_symbol)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return true;
}
///逆波兰算法
static void infixToSuffix(char *des, const char *src)
{
    SqStack symbol;
    InitStack(&symbol);
    ElemType element = 0;

    int i = 0;
    int k = 0;

    while (src[i] != '\0')
    {
        if (' ' == *(src + i)) {
            i++;
            continue;
        } else if ('(' == src[i]) {
            push(&symbol, src[i]);
        } else if (')' == src[i]) {
            while ('(' != GetTop(symbol)) {
                pop(&symbol, &element);
                des[k++] = element;
                des[k++] = ' ';
            }
            pop(&symbol, &element);
        } else if (isdigit(src[i])) {
            des[k++] = src[i];
            if (!isdigit(src[i + 1])) {
                des[k++] = ' ';
            }
        } else {
            switch (src[i]) {
                case '+':
                case '-':
                case '*':
                case '/':
                    if (Stack_is_Empty(symbol)) {
                        push(&symbol, src[i]);
                    } else {
                        if (ISTOP(src[i], GetTop(symbol))) {
                            pop(&symbol, &element);
                            des[k++] = element;
                            des[k++] = ' ';
                            continue;
                        } else {
                            push(&symbol, src[i]);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        i++;
    }
    while (!Stack_is_Empty(symbol)) {
        pop(&symbol, &element);
        des[k++] = element;
        des[k++] = ' ';
    }
    des[k] = '\0';
}
#endif

#if USE_QUEUE_WAY == USE_LIST_QUEUE
void InitQueue(sLinkQueue* iLinkQueue)
{
    iLinkQueue->fifo_in = iLinkQueue->fifo_out = NULL;
    iLinkQueue->length = 0;
}

void InQueue(sLinkQueue* iLinkQueue,ElemType element)
{
    sQueueNode *new_node = NULL;

    new_node = (sQueueNode *) malloc(sizeof(sQueueNode));
    if (0 == iLinkQueue->length)
    {
        new_node->next = iLinkQueue->fifo_in;
        iLinkQueue->fifo_in = new_node;
        iLinkQueue->fifo_out = iLinkQueue->fifo_in;
    }
    else
    {
        new_node->next = iLinkQueue->fifo_in->next;
        iLinkQueue->fifo_in->next = new_node;
        iLinkQueue->fifo_in = new_node;
    }
    new_node->data = element;
    iLinkQueue->length++;
}

void OutQueue(sLinkQueue* iLinkQueue,ElemType* element)
{
    sQueueNode *delete_node = NULL;

    if (0 == iLinkQueue->length)
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return;
    }
    else
    {
        delete_node = iLinkQueue->fifo_out;
        *element = iLinkQueue->fifo_out->data;
        iLinkQueue->fifo_out = iLinkQueue->fifo_out->next;
        free(delete_node);
        iLinkQueue->length--;
    }
}

void DestroyQueue(sLinkQueue* iLinkQueue)
{
    sQueueNode *current_node = NULL;

    if (0 == iLinkQueue->length)
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return;
    }
    else
    {
        while (iLinkQueue->length)
        {
            current_node = iLinkQueue->fifo_out;
            iLinkQueue->fifo_out = iLinkQueue->fifo_out->next;
            free(current_node);
            iLinkQueue->length--;
        }
    }
}

bool QueueEmpty(sLinkQueue iLinkQueue)
{
    if (0 == iLinkQueue.length)
        return true;
    else
        return false;
}

ElemType GetHead(sLinkQueue* iLinkQueue)
{
    if (QueueEmpty(*iLinkQueue))
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return -1;
    }
    return iLinkQueue->fifo_out->data;
}

#elif USE_QUEUE_WAY == USE_LIST_CYCLE_QUEUE
void InitQueue(sLinkQueue* iLinkQueue)
{
    iLinkQueue->fifo_in = iLinkQueue->fifo_out = NULL;
    iLinkQueue->length = 0;
}

void InQueue(sLinkQueue* iLinkQueue,ElemType element)
{
    sQueueNode *new_node = NULL;

    new_node = (sQueueNode *) malloc(sizeof(sQueueNode));
    if(NULL == new_node)
    {
        printf("%s in %d malloc failed!\n",__FUNCTION__,__LINE__);
        return;
    }
    memset(new_node, 0, sizeof(sQueueNode));

    if (QueueEmpty(*iLinkQueue))
    {
        new_node->next = new_node;
        iLinkQueue->fifo_out = iLinkQueue->fifo_in = new_node;
    }
    else
    {
        new_node->next = iLinkQueue->fifo_in->next;
        iLinkQueue->fifo_in->next = new_node;
        iLinkQueue->fifo_in = new_node;
    }
    new_node->data = element;
    iLinkQueue->length++;
}

void OutQueue(sLinkQueue* iLinkQueue,ElemType* element)
{
    sQueueNode *delete_node = NULL;

    if (QueueEmpty(*iLinkQueue))
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return;
    }
    else
    {
        delete_node = iLinkQueue->fifo_out->next;
        *element = iLinkQueue->fifo_out->data;
        iLinkQueue->fifo_in->next = iLinkQueue->fifo_out->next;
        free(iLinkQueue->fifo_out);
        iLinkQueue->fifo_out = delete_node;
        iLinkQueue->length--;
    }
}

void DestroyQueue(sLinkQueue* iLinkQueue)
{
    sQueueNode *current_node = NULL;

    if (QueueEmpty(*iLinkQueue))
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return;
    }
    else
    {
        while (iLinkQueue->length)
        {
            current_node = iLinkQueue->fifo_out;
            iLinkQueue->fifo_in->next = iLinkQueue->fifo_out->next;
            iLinkQueue->fifo_out = iLinkQueue->fifo_out->next;
            free(current_node);
            iLinkQueue->length--;
        }
    }
}

ElemType GetHead(sLinkQueue* iLinkQueue)
{
    if (QueueEmpty(*iLinkQueue))
    {
        printf("[%s]ERROR\n", __FUNCTION__);
        return -1;
    }
    return iLinkQueue->fifo_out->data;
}

bool QueueEmpty(sLinkQueue iLinkQueue)
{
    if (0 == iLinkQueue.length)
        return true;
    else
        return false;
}

#elif USE_QUEUE_WAY == USE_SEQUENTIAL_QUEUE
#endif

#if USE_STACK_QUEUE_WAYS == USE_STACK_WAY
void Stack_FunctionTest(void)
{
#if USE_STACK_WAY == USE_SEQUENTIAL_STACK
    ElemType ele;
    bool ret=false;
    sStack stack1;
    ret=InitStack(&stack1);
    if(ret)
    {
        push(&stack1,12);
        pop(&stack1,&ele);
        push(&stack1,45);
        push(&stack1,78);
        push(&stack1,123);
        int length=StackLength(stack1);
        printf("%d\n",length);
    }

#elif USE_STACK_WAY == USE_MOLLOC_STACK
    ElemType ele;
    SqStack stack2;
    InitStack(&stack2);
    push(&stack2,123);
    push(&stack2,0x87654321);
    push(&stack2,0x55);
    push(&stack2,0xaa);
//    DestroyStack(&stack2);
    int len=StackLength(stack2);
    printf("len:%d\n",len);
    printf("top:%d\n",GetTop(stack2));
    printf("len:%d\n",len);
//    BintoHexOrOct(OTC);
//    printf("num:%d\n",num);
    char src[]="1+(1+2*5)-9";
    char des[20]={0};
    infixToSuffix(des,src);
    printf("%s\n",des);
#elif USE_STACK_WAY == USE_LIST_STACK
    sLinkStack stack1;
    ElemType ele;

    InitStack(&stack1);
    push(&stack1,10);
    push(&stack1,11);
    push(&stack1,12);
    push(&stack1,13);
    pop(&stack1,&ele);
    printf("ele:%d\n",ele);
//    pop(&stack1,&ele);
//    pop(&stack1,&ele);
//    pop(&stack1,&ele);
//    pop(&stack1,&ele);
    printf("Get:%d\n",GetTop(stack1));
    DestroyStack(&stack1);
#endif
}
#endif

#if USE_STACK_QUEUE_WAYS == USE_QUEUE_WAY
void Queue_FunctionTest(void)
{
    sLinkQueue queue1;
    ElemType data=0;

    InitQueue(&queue1);
    InQueue(&queue1,10);
    InQueue(&queue1,145);
    InQueue(&queue1,963);
    InQueue(&queue1,456);

    printf("data:%d\n",data);
    OutQueue(&queue1,&data);
    printf("data:%d\n",data);
    OutQueue(&queue1,&data);
    printf("data:%d\n",data);
    OutQueue(&queue1,&data);
    printf("data:%d\n",data);
    printf("len:%d\n",queue1.length);
}
#endif