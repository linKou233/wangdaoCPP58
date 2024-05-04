#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//用动态数组实现队列，用循环数组来实现
#define Default_Capacity 3

typedef int E;

typedef struct {
    E* elements;
    int front;          //队头
    int rear;           //队尾
    int size;           //实际大小
    int capacity;       //容量
} Queue;

// API
Queue* queue_create(E capacity) {    //创造一个队列
    Queue *q = (Queue*)malloc(sizeof(Queue)); 
    if(!q){
        printf("Error: failed to create a new Queue!");
        exit(1);
    }

    E *e = (E*)malloc(capacity * sizeof(E));
    if(!e){
        printf("Error: failed to create a new Vector!");
        exit(1);
    }

    q->elements = e;
    q->front = 0;                       //队头指针
    q->rear = 0;                        //队尾指针
    q->size = 0;                        //队列的实际大小
    q->capacity = capacity;             //队列的容量

    return q;
}

bool queue_empty(Queue* q) {//判队列是否为空,队空返回true
    if(q->size == 0)
        return true;
    return false;
}

bool queue_full(Queue* q) {//判断队列是否满，队满返回true
    if(q->capacity == q->size)
        return true;
    return false;
}

void queue_destroy(Queue* q) {//销毁一个队列
    free(q->elements);
    free(q);
}

void grow_capacity(Queue *q) {//队列扩容
    E new_capacity = q->capacity + Default_Capacity;        //线性扩容
    E *new_elements = (E*)malloc(new_capacity * sizeof(E));

    int cnt = q->size, i=0;
    while(q->size != 0){                     //将老数组按照从队头元素依次赋给新数组
        new_elements[i] = q->elements[q->front];
        q->front = (q->front+1) % q->capacity;
        i++;
        q->size--;
    }
    //设置新的队头和队尾以及size和capacity
    q->front = 0;
    q->rear = i;
    q->size = cnt;
    q->capacity = new_capacity;

    free(q->elements);               
    q->elements = new_elements;  //将队列指向新的动态数组
    printf("扩容完成！\n");
}

void queue_push(Queue* q, E val) {    //入队
    if(queue_full(q)){                //判断是否队满
        printf("队列此时满了，需要扩容！\n");
        grow_capacity(q);
    }
    //队尾入队
    q->size++;
    q->elements[q->rear] = val;       
    q->rear = (q->rear+1)% q->capacity;
}

E queue_pop(Queue* q) {           //出队
    if(queue_empty(q)){           //判断是否队空
        printf("队已空，出队失败！");
        exit(1);
    }
    //队头出队
    q->size--;
    E data = q->elements[q->front];
    q->front = (q->front+1) % q->capacity;

    return data; 
}

E queue_peek(Queue* q) {     //查看队头元素并且返回
    E data = q->elements[q->front];
    
    return data;
}

int main(){
    Queue *q = queue_create(Default_Capacity);
    //*1 测试正常的入队出队和循环    队列空间默认为3
        queue_push(q, 1);
        queue_push(q, 2);
        queue_push(q, 3);
        printf("队列此时的最大容量为：%d\n", q->capacity);
        printf("测试queue_peek函数：%d\n", queue_peek(q));      //1
        printf("%d\n", queue_pop(q));       //1
        queue_push(q, 4);
        printf("%d\n", queue_pop(q));      //2
        printf("%d\n", queue_pop(q));      //3
        printf("%d\n", queue_pop(q));      //4
        //此时队列为空了
        if(queue_empty(q))
            printf("队列此时为空!\n");
        else
            printf("队列此时不为空！\n");
    //*2 测试能否扩容以及扩容后的循环
        queue_push(q, 1);
        queue_push(q, 2);
        queue_push(q, 3);
        //开始扩容
        queue_push(q, 4);
        printf("队列此时的最大容量为：%d\n", q->capacity);
        queue_push(q, 5);
        queue_push(q, 6);
        //开始扩容
        queue_push(q, 7);
        printf("队列此时的最大容量为：%d\n", q->capacity);
        queue_pop(q);       //弹出1， 剩余2、3、4、5、6、7、8
        queue_push(q, 8);
        while(q->size != 0){
            printf("%d ", queue_pop(q));
        }
    queue_destroy(q);

    return 0;
}