//
// Created by ASUS on 2022/4/20 0020.
//

#ifndef CLION_FIFO_H
#define CLION_FIFO_H

#define AFIFO_INIT(name, type, size)               \
    static const unsigned int name##_FIFO_SIZE = size; \
    static type name##_fifo[size] = {0};           \
    static unsigned int name##_fifo_in = 0;            \
    static unsigned int name##_fifo_out = 0;

#define AFIFO_IN(name, x)                                               \
    ({                                                                  \
        name##_fifo[name##_fifo_in] = x;                                \
        name##_fifo_in = (name##_fifo_in + 1) & (name##_FIFO_SIZE - 1); \
    })

#define AFIFO_OUT(name, type)                                             \
    ({                                                                    \
        type val = name##_fifo[name##_fifo_out];                          \
        name##_fifo_out = (name##_fifo_out + 1) & (name##_FIFO_SIZE - 1); \
        val;                                                              \
    })

#define AFIFO_IS_EMPTY(name) (name##_fifo_in == name##_fifo_out)

#define AFIFO_IS_FULL(name) (((name##_fifo_in + 1) & (name##_FIFO_SIZE - 1)) == name##_fifo_out)

#define AFIFO_RESET(name) (name##_fifo_out = name##_fifo_in)

#endif //CLION_FIFO_H
