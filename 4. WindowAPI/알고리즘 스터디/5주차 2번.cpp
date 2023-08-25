class Solution {
public:
    vector<int> countBits(int n)
    {
        vector<int> ans;
        if (n == 0)
        {
            ans.push_back(0);
            return ans;
        }

        ans.push_back(0);
        ans.push_back(1);

        int interval = 2;
        for (int i = 2; i <= n; i++)
        {
            if (i - interval >= interval) interval *= 2;
            ans.push_back(ans[i - interval] + 1);
        }

        return ans;
    }
};