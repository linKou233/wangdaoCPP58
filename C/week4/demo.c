#include <stdio.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* rotateRight(Node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }
    Node* current = head;
    int len = 1;
    while (current->next != NULL) {
        current = current->next;
        len++;
    }
    current->next = head;

    k = len - k % len;
    while (k-- > 0) {
        current = current->next;
    }
    head = current->next;
    current->next = NULL;

    return head;
}