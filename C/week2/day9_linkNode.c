#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int data;
    struct node_s* next;
} Node;

// a)头插法
void add_before_head(Node* plist, int val) {
    
    Node *node = (Node*)malloc(sizeof(Node));
    node->next =NULL;
    node->data = val;
    
    node->next = plist->next;
    plist->next = node;
    (plist->data)++;
}

// b)打印链表所有值
void display_list(Node* list) {
    while(list != NULL) {
        printf("%d->", list->data);
        list = list->next;
    }
    printf("NULL");
}

// c)   查找结点，失败则返回NULL
Node* search_list(Node* list, int val) {
    while(list != NULL){
        if(list->data == val)
            return list;
        list = list->next;
    }
    return NULL;
}

// d)   释放所有结点
void free_list(Node* list) {
    while(list != NULL){
        Node *p = list;
        list = p->next;
        free(p);
    }
}

int main(){
    Node *head = (Node*)malloc(sizeof(Node));
    head -> data = 0;
    head -> next = NULL;
    add_before_head(head, 7);
    add_before_head(head, 8);
    add_before_head(head, 9);

    display_list(head->next);
    search_list(head, 9);
    free(head);

    return 0;
}