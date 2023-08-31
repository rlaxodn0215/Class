class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        // We need only numbers Not array..!!
        int ans = 0;
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        int compareNum = intervals.front()[1];

        for (int i = 1; i < n; i++)
        {
            if (compareNum > intervals[i][0]) // overlap
            {
                ans++; // one if them should erase...
                compareNum = min(compareNum, intervals[i][1]); // should compare small one
            }

            else
            {
                compareNum = max(compareNum, intervals[i][1]); // before one is finished
            }
        }

        return ans;
    }
};