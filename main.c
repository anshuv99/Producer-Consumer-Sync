#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "queue.h"
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"
#include "struct_args.h"

int main() {

    // Thread initialisation
    pthread_t reader;
    pthread_t munch1;
    pthread_t munch2;
    pthread_t writer;


    // Queue initialisation
    Queue *readerToMunch1 = CreateStringQueue(10);
    Queue *munch1ToMunch2 = CreateStringQueue(10);
    Queue *munch2ToWriter = CreateStringQueue(10);
    struct_args *structMunch1 = (struct_args*) malloc(sizeof(struct_args));
    struct_args *structMunch2 = (struct_args*) malloc(sizeof(struct_args));
    structMunch1->q1 = readerToMunch1;
    structMunch1->q2 = munch1ToMunch2;
    structMunch2->q1 = munch1ToMunch2;
    structMunch2->q2 = munch2ToWriter;

    // Testing purposes
    EnqueueString(munch2ToWriter, "abc");
    EnqueueString(munch2ToWriter, "defg");
    EnqueueString(munch2ToWriter, "hijk");
    EnqueueString(munch2ToWriter, NULL);

    // thread Creation
    if(pthread_create(&reader, NULL, readInput, readerToMunch1) != 0){
        printf("Thread Creation Failed for reader");
        return 2;
    }
    if(pthread_create(&munch1, NULL, replaceBlanks, structMunch1)!= 0){
        printf("Thread Creation Failed for Munch1");
        return 2;
    }
    if(pthread_create(&munch2, NULL, convertToLowerCase, structMunch2)!= 0){
        printf("Thread Creation Failed for Munch2");
        return 2;
    }

    if(pthread_create(&writer, NULL, printOutput, (void *)munch2ToWriter)){
        printf("Thread Creation Failed for Writer");
        return 0;
    }

    // thread Destroy
    if(pthread_join(reader, (void **) NULL) != 0){
        printf("Thread join Failed for Reader");
        return 2;
    }
    if(pthread_join(munch1, (void **) NULL) != 0){
        printf("Thread join Failed for Munch1");
        return 2;
    }
    if(pthread_join(munch2, (void **) NULL) != 0){
        printf("Thread join Failed for Munch2");
        return 2;
    }
    if (pthread_join(writer, (void **) NULL) != 0){
        printf("Thread join Failed for Writer");
        return 2;
    }


    PrintQueueStats(munch2ToWriter);
    return 0;
}