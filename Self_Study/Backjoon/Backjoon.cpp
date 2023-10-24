#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<string>
#include<map>

using namespace std;

int findMin(vector<int>& nums)
{
    int n = nums.size();
    int start = 0;
    int mid = n / 2;
    int end = n - 1;
    int size = n;
    int ans = 1000;

    while (size > 0)
    {
        if (nums[start] > nums[mid])
        {
            ans = min(ans, nums[mid]);
            end = mid - 1;
            mid = (start + end) / 2;
        }

        else if (nums[mid] > nums[end])
        {
            ans = min(ans, nums[end]);
            start = mid + 1;
            mid = (start + end) / 2;
        }

        else
        {
            ans = min(ans, nums[start]);
        }

        size /= 2;
    }

    return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    vector<int> nums = { 57,58,59,62,63,66,68,72,73,74,75,76,77,78,80,81,86,95,96,97,98,100,101,102,
        103,110,119,120,121,123,125,126,127,132,136,144,145,148,149,151,152,160,161,163,166,168,169,
        170,173,174,175,178,182,188,189,192,193,196,198,199,200,201,202,212,218,219,220,224,225,229,
        231,232,234,237,238,242,248,249,250,252,253,254,255,257,260,266,268,270,273,276,280,281,283,
        288,290,291,292,294,295,298,299,4,10,13,15,16,17,18,20,22,25,26,27,30,31,34,38,39,40,47,53,54 };

    cout << findMin(nums) << endl;
	return 0;
}




