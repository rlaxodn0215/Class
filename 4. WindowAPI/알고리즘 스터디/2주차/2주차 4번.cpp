class Solution {
public:
    int hammingWeight(uint32_t n)
    {
        unsigned int num = n;
        int ans = 0;

        while (num != 0)
        {
            if (num > (num * 2))
            {
                ans++;
            }
            num *= 2;
        }

        return ans;
    }
};