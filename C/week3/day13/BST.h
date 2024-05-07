typedef int K;

typedef struct tree_node {
	K key;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;

typedef struct {
	TreeNode* root;
} BST;

// API
BST* bst_create(void);
void bst_destroy(BST* tree);		//要实现的函数

void bst_insert(BST* tree, K key);
TreeNode* bst_search(BST* tree, K key);
void bst_delete(BST* tree, K key);

// 深度优先遍历
void bst_preorder(BST* tree);		//实现先序遍历和后序遍历
void bst_inorder(BST* tree);
void bst_postorder(BST* tree);
// 广度优先遍历
void bst_levelorder(BST* tree);
void bst_levelorder2(BST* tree);		//实现广度优先遍历