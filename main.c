#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "test.h"
#include "ADT_List.h"
#include "fifo.h"
#include "Function_Test.h"
#pragma pack(4)

typedef struct {
    int num;
    const char *string;
    char arr[];
} sStruct;

AFIFO_INIT(arr, unsigned int, 8);

#include<stdio.h>
#include<stdlib.h>


/*将相应的枚举类型转为字符串(这种方法很重要)*/
#define FOREACH_CMD(CMD) \
        CMD(CMD_UNSPEC),   \
        CMD(CMD_ADD),  \
        CMD(CMD_SUB),   \
        CMD(CMD_MULTI),
#define GENERATE_ENUM(ENUM) ENUM
#define GENERATE_STRING(STRING) #STRING

enum CMD_ENUM {
    FOREACH_CMD(GENERATE_ENUM)
};

static const char *CMD_STRING[] = {
        FOREACH_CMD(GENERATE_STRING)
};

int main(void)
{
    sStruct *p = NULL;
    const char str[] = "string";

#define enumtostring(x) #x
#define STR(x)  enumtostring(x)
typedef enum{
    ONE,
    TWO,
}eNUM;
eNUM n=ONE;
printf("%s\n",enumtostring(ONE));
    printf("%s\n",STR(n));

    printf("%s\n", CMD_STRING[CMD_ADD]);
    Function_Test();
    p = (sStruct *) malloc(sizeof(sStruct) + sizeof(str));
    p->num = 1;
    p->string = str;
    memcpy(p->arr, str, sizeof(str));
    printf("p->num:%d,p->string:%s,p->arr:%s\n", p->num, p->string, p->arr);


//    AFIFO_IN(arr, 2);
    for (unsigned int i = 0; i < arr_FIFO_SIZE; i++)
    {
        AFIFO_IN(arr, i);
        printf("%d", arr_fifo[i]);
    }
    for (unsigned int i = 0; i <= arr_FIFO_SIZE; i++)
    {
        printf("%d", AFIFO_OUT(arr,unsigned int));
    }
    printf("\nfull: %d,empty:%d\n",AFIFO_IS_FULL(arr),AFIFO_IS_EMPTY(arr));

    system("pause");
    return 0;
}


