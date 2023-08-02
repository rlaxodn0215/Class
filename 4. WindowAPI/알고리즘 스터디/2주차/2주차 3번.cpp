class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        int max = 0; //max difference
        int min = prices[0]; //first num
        int n = prices.size();

        for (int i = 1; i < n; i++)
        {
            if (min > prices[i]) // if new min num found, max num of less than index i cannot use 
            {
                min = prices[i];
                continue;
            }

            max = (max > prices[i] - min) ? max : prices[i] - min; // find max difference

        }

        return max;
    }
};