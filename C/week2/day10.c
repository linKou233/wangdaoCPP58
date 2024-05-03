//leetcode  876、141、206、21

//day10_5 用单链表实现栈
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int E;

typedef struct node {
    E data;
    struct node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} Stack;

// API
Stack* stack_create(void) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    s->size =0;

    return s;
}

bool stack_empty(Stack* s) {
    if( s->top == NULL)     //栈空
        return true;
    return false;
}

void stack_destroy(Stack* s){
    while(!stack_empty(s)){
        Node *tmp = s->top;
        s->top = tmp->next;
        free(tmp);
    }
    free(s);
}

void stack_push(Stack* s, E val){
    Node *node =(Node*)malloc(sizeof(Node));
    node->data = val;
    
    node->next = s->top;
    s->top = node;
    s->size++;
}

E stack_pop(Stack* s) {
    //先判断栈空
    if(stack_empty(s)){
        printf("栈空，删除失败");
        exit(1);
    }
    Node *tmp = s->top;
    int data = tmp->data;
    s->top = tmp->next;
    
    return data;
}
E stack_peek(Stack* s) {
    Node *tmp = s->top;
    E data; 

    while(tmp){
        data = tmp->data;
        tmp = tmp->next;
    }
    return data;
}


int main(){
    Stack *s = stack_create();
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_push(s, 4);
    printf("%d\n", stack_pop(s));
    printf("%d\n", stack_peek(s));
    stack_push(s, 5);
    printf("%d\n", stack_pop(s));
    printf("%d\n", stack_peek(s));

    stack_destroy(s);

    return 0;
}

