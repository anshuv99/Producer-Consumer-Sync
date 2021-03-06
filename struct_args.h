//
// Created by Anshu on 10/18/18.
// Co-author Arpit Jain
//

#ifndef OS_HW2_STRUCT_ARGS_H
#define OS_HW2_STRUCT_ARGS_H

#endif //OS_HW2_STRUCT_ARGS_H

#ifndef OS_HW2_QUEUE_H
#define OS_HW2_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#endif //OS_HW2_QUEUE_H

typedef struct struct_args{
    Queue *q1;
    Queue *q2;
}struct_args;


struct_args* getCombinedQueue(Queue *q1, Queue *q2);