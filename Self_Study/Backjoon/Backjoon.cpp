#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<string>
#include<map>

using namespace std;

vector<int> Sum(vector<int>& nums, int target);

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<int> nums0 = { 7,2,15,11 };
	int target0 = 9;
	vector<int> nums1 = { 3,2,1,5,4 };
	int target1 = 11;
	vector<int> nums2 = { 2,5,4,3,1 };
	int target2 = 10;

	vector<int> ans0 = Sum(nums0, target0);
	vector<int> ans1 = Sum(nums1, target1);
	vector<int> ans2 = Sum(nums2, target2);

	for (int i = 0; i < ans0.size(); i++)
	{
		cout << ans0[i] << " ";
	}

	cout << "\n";

	for (int i = 0; i < ans1.size(); i++)
	{
		cout << ans1[i] << " ";
	}

	cout << "\n";

	for (int i = 0; i < ans2.size(); i++)
	{
		cout << ans2[i] << " ";
	}

	cout << "\n";

	return 0;
}

vector<int> Sum(vector<int>& nums, int target)
{
	vector<vector<int>> num;

	map<int, int> temp;
	
	for (int i = 0; i < nums.size(); i++)
	{
		temp[target - nums[i]] = i;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (temp[nums[i]] && temp[nums[i]] !=i)
		{
			vector<int> ans = {i,temp[nums[i]]};
			num.push_back(ans);
		}
	}

	sort(num.begin(), num.end());

	if (num.empty())
	{
		vector<int> none = { -1 };
		return none;
	}

	return num[0];
}


