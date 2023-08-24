class Solution
{
public:
    bool containsDuplicate(vector<int>& nums)
    {
        bool ans = false;
        map<int, int> temp;

        for (int i = 0; i < nums.size(); i++)
        {
            if (temp.count(nums[i])) // is map has a key?
            {
                ans = true;
                break;
            }

            else
            {
                temp[nums[i]] = i;
            }
        }

        return ans;
    }
};