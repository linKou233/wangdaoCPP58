/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
//leetcode 104二叉树的的深度

// int traversal(struct TreeNode* root, int deep) {
//     if(root ==NULL) return deep;
//     deep++;
//     int left = traversal(root->left, deep);
//     int right = traversal(root->right, deep);

//     return left > right ? left:right;
// }

// int maxDepth(struct TreeNode* root) {
//     return traversal(root, 0);
// }