#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Vector.c"

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// Ԫ
int main(void) {
	Vector* v = vector_create();
	
	for (int i = 0; i < 10; i++) {
		push_back(v, i);
	}
	
	printf("%d\n", pop_back(v));
	printf("%d\n", pop_back(v));
	printf("%d\n", pop_front(v));
	printf("%d\n", pop_front(v));
	push_front(v, 10);
	printf("%d\n", pop_front(v));
	
	
	vector_destroy(v);
	return 0;
}
