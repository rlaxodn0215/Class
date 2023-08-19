class Solution
{
    vector<int> pVal;
    vector<int> qVal;

public:

    void TreeInfo(TreeNode* temp, vector<int>& vec)
    {
        if (temp == NULL)
        {
            vec.push_back(INT_MAX);
            return;
        }

        vec.push_back(temp->val);

        TreeInfo(temp->left, vec);
        TreeInfo(temp->right, vec);
    }

    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        TreeInfo(p, pVal);
        TreeInfo(q, qVal);

        return (pVal == qVal);
    }
};