//
// Created by Rougga on 2022/5/25 0025.
//

#ifndef CLION_ADT_STRING_H
#define CLION_ADT_STRING_H

#pragma pack(4)

typedef struct string
{
    int str_length;
    char str[];
}String;

typedef char* string;

void Get_next(const char *T, int *next);
void Get_nextval(const char *T, int *nextval);
int match_string(const char* dst, const char* src, int pos);
int Index_KMP(const char* S, const char* T, int pos);
#endif //CLION_ADT_STRING_H
