//
// Created by Rougga on 2022/5/25 0025.
//

#include "ADT_String.h"

///> 字符串模式匹配,朴素匹配
int match_string(const char *dst, const char *src, int pos) {
    int idst = 0, isrc = 0;
    int index = -1;

    idst = pos;

    if (!dst || !src) {
        return -1;
    } else {
        while ('\0' != dst[idst]) {
            if (src[isrc] == dst[idst]) {
                if (0 == isrc)index = idst;
                isrc++;
                idst++;
                continue;
            }
            if ('\0' == src[isrc]) {
                break;
            }
            isrc = 0;
            idst++;
        }
        if (src[isrc] != '\0')
            index = -1;
        return index;
    }
}

void Get_next(const char *T, int *next) {
    int i, j;
    i = 1;//后缀
    j = 0;//前缀
    next[1] = 0;
    while (i < T[0])    //T[0]:记录串 T 长度
    {
        /* T[i]:表示后缀的单个字符
         * T[j]:表示前缀的单个字符
         * */
        if (0 == j || T[i] == T[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];//字符不同，则 j 回溯
        }
    }
}

void Get_nextval(const char *T, int *nextval) {
    int i, j;
    i = 1;//后缀
    j = 0;//前缀
    nextval[1] = 0;
    while (i < T[0])    //T[0]:记录串 T 长度
    {
        /* T[i]:表示后缀的单个字符
         * T[j]:表示前缀的单个字符
         * */
        if (0 == j || T[i] == T[j]) {
            ++i;
            ++j;
            if (T[i] != T[j])            //如果当前字符和前缀字符不相等，则将前缀的 j 赋值给 nextval 在i位置上的值
                nextval[i] = j;
            else                        //如果当前字符和前缀字符相等,则将前缀的 nextval 赋值给 nextval 在i位置上的值
                nextval[i] = nextval[j];
        } else {
            j = nextval[j];//字符不同，则 j 回溯
        }
    }
}

/* 返回子串T在主串S中第pos个字符之后的位置，若不存在，返回0
 * T非空，1<=pos<=strlenth(S)
 * */
int Index_KMP(const char *S, const char *T, int pos) {
    int i = pos;    //主串S当前的下标值,若 pos != 1,则从pos位置匹配
    int j = 1;      //j 用于子串 T 当前的下标值
    int next[255] = {0};

//    Get_next(T,next);
    Get_nextval(T, next);

    while (i <= S[0] && j <= T[0]) {
        if (0 == j || S[i] == T[j]) {    //两个字母相等，继续
            ++i;
            ++j;
        } else {
            j = next[j];    // j 回溯到合适位置
        }
    }

    if (j > T[0])
        return i - T[0];
    else
        return 0;
}