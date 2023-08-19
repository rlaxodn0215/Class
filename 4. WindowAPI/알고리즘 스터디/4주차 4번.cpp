class Solution
{
    int arr[20001];

public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            arr[nums[i] + 10000]++;
        }

        vector<pair<int, int>> val;

        for (int i = 0; i < 20000; i++)
        {
            if (arr[i] == 0) continue;
            val.push_back({ arr[i],i - 10000 });
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>> temp;

        for (int i = 0; i < val.size(); i++)
        {
            temp.push(val[i]);
        }

        vector<int> ans;

        for (int i = 0; i < k; i++)
        {
            int num = temp.top().second;
            temp.pop();
            ans.push_back(num);
        }

        return ans;
    }
};