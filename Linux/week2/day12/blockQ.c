#include "blockQ.h"

BlockQ* blockq_create(void) {
    BlockQ *q = (BlockQ*)malloc(sizeof(BlockQ));
    if(!q) {
        perror("malloc");
        return NULL;
    }
    q->front = q->rear = q->size = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);

    return q;
}

void blockq_destroy(BlockQ* q) {
    pthread_mutex_destroy(&q->mutex);
    pthread_mutex_destroy(&q->not_empty);
    pthread_mutex_destroy(&q->not_full);
    free(q);
}

bool blockq_empty(BlockQ* q) {
    pthread_mutex_lock(&q->mutex);
    bool empty = (q->size == 0);
    pthread_mutex_unlock(&q->mutex);
    
    return empty;
}

bool blockq_full(BlockQ* q) {
    pthread_mutex_lock(&q->mutex);
    bool full = (q->size == N);
    pthread_mutex_unlock(&q->mutex);

    return full;
}

void blockq_push(BlockQ* q, E val) {
    pthread_mutex_lock(&q->mutex);
    while (q->size == N)
    {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    q->elements[q->rear] = val;
    q->rear = (q->rear + 1) % N;
    q->size++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

E blockq_pop(BlockQ* q) {
    pthread_mutex_lock(&q->mutex);
    while (q->size == 0)
    {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    E val = q->elements[q->front];
    q->front = (q->front + 1) % N;
    q->size--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
    
    return val;
}

E blockq_peek(BlockQ* q) {
    pthread_mutex_lock(&q->mutex);
    while (q->size == 0) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    E retval = q->elements[q->front];
    pthread_mutex_unlock(&q->mutex);
    return retval;
}