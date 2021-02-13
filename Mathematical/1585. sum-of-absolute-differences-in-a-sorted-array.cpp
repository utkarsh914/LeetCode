// https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/

class Solution {
public:
	vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
		int size = nums.size();
		// presum is 1 indexed
		vector<int> presum(size+1);
		for (int i=1; i<presum.size(); i++)
			presum[i] = presum[i-1]+nums[i-1];

		vector<int> result(size);
		for (int i=1; i<=size; i++) {
			int left = (presum[i-1]) - nums[i-1]*(i-1);
			int right = (presum[size]-presum[i]) - nums[i-1]*(size-i);
			result[i-1] = (abs(left)+right);
		}

		return result;
	}
};



// more cleaner *******
vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
	const int N = nums.size();
	vector<int> ans(N, 0);
	ans[0] = accumulate(nums.begin(), nums.end(), 0) - (N * nums[0]);
	for (int i = 1; i < N; i++)
		ans[i] = ans[i-1] + (nums[i] - nums[i-1]) * i - (nums[i] - nums[i-1]) * (N-i); 
	return ans;
}

/*
One thing keep in mind is that it is a sorted array
if array is [ 1 4 6 8 10 ]
for element 6 diff are 5 ,2, 0 , 2, 4 now
for 8 diffrs are going to be 5+(8-6) , 2+(8-6) , 0+(8-6) , 2+(6-8) , 4+(6 - 8) => 7 4 2 0 2 = 15
same way for 10 diffrs  are going to be  7+(10-8) , 4+(10-8) , 2+(10-8) , 0+(10-8) , 2+(8 - 10) = > 9 6 4 2 0
Hope it clear now
*/