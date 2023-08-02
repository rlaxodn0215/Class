class Solution
{
    int depth = 0;
    int max = 0;
public:
    int maxDepth(TreeNode* root)
    {
        depth++;
        if (root == NULL) //if node not exist
        {
            depth--; //go back
            return(max);
        }
        if (root->left == NULL && root->right == NULL) //if node is last
        {
            max = (max > depth) ? max : depth; //compare the biggest
            depth--; //go back
            return(max);
        }

        maxDepth(root->left); //go left
        maxDepth(root->right); //go right
        depth--; // go back after searching left and right
        return max;
    }
};