#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "BST.c"

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	BST* tree = bst_create();

	bst_insert(tree, 9);
	bst_insert(tree, 42);
	bst_insert(tree, 57);
	bst_insert(tree, 5);
	bst_insert(tree, 3);
	bst_insert(tree, 13);

	TreeNode* node1 = bst_search(tree, 42);
    printf("%d\n", node1->key);
	//TreeNode* node2 = bst_search(tree, 9527);
    

	// bst_delete(tree, 3);
	// bst_delete(tree, 5);
	bst_delete(tree, 9);

	
    // 
	bst_preorder(tree);
    bst_inorder(tree);
    bst_postorder(tree);
	// 
	// α
	bst_levelorder(tree);
    
    printf("-------------\n");
    bst_levelorder2(tree);
	return 0;
}