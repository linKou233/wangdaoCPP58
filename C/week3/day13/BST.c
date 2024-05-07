#include "BST.h"
#include "Queue.c"
#include <stdlib.h>
#include <stdio.h>

BST* bst_create(void) {
	return (BST*)calloc(1, sizeof(BST));
}

void bst_insert(BST* tree, K key) {
	// 1. 找到添加的位置
	TreeNode* parent = NULL;
	TreeNode* curr = tree->root;

	int cmp;
	while (curr) {
		cmp = key - curr->key;
		if (cmp < 0) {
			parent = curr;
			curr = curr->left;
		} else if (cmp > 0) {
			parent = curr;
			curr = curr->right;
		} else {
			// key 已存在
			return;
		}
	}	// curr == NULL, cmp = key - parent->key
	// 2. 添加节点
	// a. 创建节点并初始化
	TreeNode* newnode = (TreeNode*)calloc(1, sizeof(TreeNode));
	newnode->key = key;
	// b. 链接
	if (parent == NULL) {
		tree->root = newnode;
	} else if (cmp < 0) {
		parent->left = newnode;
	} else {
		parent->right = newnode;
	}
}

TreeNode* bst_search(BST* tree, K key) {
	TreeNode* curr = tree->root;
	while (curr) {
		int cmp = key - curr->key;
		if (cmp < 0) {
			curr = curr->left;
		} else if (cmp > 0) {
			curr = curr->right;
		} else {
			return curr;
		}
	} // curr == NULL
	return NULL;
}

void bst_delete(BST* tree, K key) {
	// 1. 找到删除的节点
	TreeNode* parent = NULL;
	TreeNode* curr = tree->root;
	while (curr) {
		int cmp = key - curr->key;
		if (cmp < 0) {
			parent = curr;
			curr = curr->left;
		} else if (cmp > 0) {
			parent = curr;
			curr = curr->right;
		} else {
			break;
		}
	} // curr == NULL || curr != NULL
	if (curr == NULL) return;
	// 2. 删除 curr 节点
	if (curr->left && curr->right) {
		// 退化成度为0或者度为1的情况
		TreeNode* minp = curr;
		TreeNode* min = curr->right;
		while (min->left) {
			minp = min;
			min = min->left;
		}
		// 退化
		curr->key = min->key;
		curr = min;
		parent = minp;
	}
	
	// 找到唯一的孩子
	TreeNode* child = curr->left ? curr->left : curr->right;

	if (parent == NULL) {
		tree->root = child;
	} else {
		// 将child链接到parent的正确位置
		int cmp = curr->key - parent->key;	// Caution: 得重新比较
		if (cmp < 0) {
			parent->left = child;
		} else if (cmp > 0) {
			parent->right = child;
		} else {
			// Caution: 可能cmp == 0
			parent->right = child;
		}
	}
	free(curr);
}

void inorder(TreeNode* root) {
	// 边界条件
	if (root == NULL) {
		return;
	}
	// 递归公式
	// 遍历左子树
	inorder(root->left);
	// 遍历根结点
	printf("%d ", root->key);
	// 遍历右子树
	inorder(root->right);
}

void bst_inorder(BST* tree) {
	inorder(tree->root);
	printf("\n");
}

// 层次遍历
void bst_levelorder(BST* tree) {
	Queue* q = queue_create();
	// 将根结点入队列
	queue_push(q, tree->root);
	// 判断队列是否为空
	while (!queue_empty(q)) {
		// 出队列，遍历这个节点
		TreeNode* node = queue_pop(q);
		printf("%d ", node->key);
		// 判断是否有左孩子
		if (node->left) {
			queue_push(q, node->left);
		}
		// 判断是否有右孩子
		if (node->right) {
			queue_push(q, node->right);
		}
	} // queue_empty(q)
	printf("\n");
}

//前序遍历
void preorder(TreeNode* root) {
	if(root == NULL)
		return;
	printf("%d ", root->key);
	preorder(root->left);
	preorder(root->right);
}
void bst_preorder(BST* tree) {
	preorder(tree->root);
	printf("\n");
}

//后序遍历
void postorder(TreeNode *root) {
	if(root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ",root->key);
}
void bst_postorder(BST* tree) {
	postorder(tree->root);
	printf("\n");
}

// 销毁二叉搜索树
void destroy(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    destroy(root->left);
    destroy(root->right);
    free(root);
}
void bst_destroy(BST* tree) {
    destroy(tree->root);
    free(tree);
}

// 层次遍历（使用两个队列实现）
void bst_levelorder2(BST* tree) {
    Queue* q1 = queue_create();
    Queue* q2 = queue_create();
    
	queue_push(q1, tree->root);
    while (!queue_empty(q1) || !queue_empty(q2)) {
        while (!queue_empty(q1)) {
            TreeNode* node = queue_pop(q1);
            printf("%d ", node->key);
            if (node->left) {
                queue_push(q2, node->left);
            }
            if (node->right) {
                queue_push(q2, node->right);
            }
        }
        printf("\n");
        while (!queue_empty(q2)) {
            TreeNode* node = queue_pop(q2);
            printf("%d ", node->key);
            if (node->left) {
                queue_push(q1, node->left);
            }
            if (node->right) {
                queue_push(q1, node->right);
            }
        }
        printf("\n");
    }
    queue_destroy(q1);
    queue_destroy(q2);
}