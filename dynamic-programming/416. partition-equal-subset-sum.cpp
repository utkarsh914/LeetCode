// https://leetcode.com/problems/partition-equal-subset-sum/

/*
Given a non-empty array nums containing only positive integers,
find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.

*/




// using BITSET
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		bitset<10001> bits(1);
		int sum = accumulate(nums.begin(), nums.end(), 0);
		for (auto n : nums) bits |= bits << n;
		return !(sum & 1) && bits[sum >> 1];
	}
};
/*
Explanation of the above code :
Size of bitset is the maximum sum that can be achieved by array + 1.
Ex. [5,2,4] ---> bitset of size 12 ==> 000000000001
That means initially we can achieve sum 0 with empty array subset [ ].
We have only 0's bit set.

num = 5
0 -> 5 (set 5's bit, since we can achieve sum 5.)
Now we can achieve 0 and 5 with [ ] and [ 5 ]. So by the union of both, we have 000000100001

num = 2
0->2
5->7
We can achieve 0,2,5,7 from [5,2] ==> [ ], [5], [2], [5,2]
After union our bitset is 000010100101

num = 4
0->4
2->6
5->9
7->11
We can achieve 0,2,4,5,6,7,11 from [5,2] ==> [ ], [5], [2], [4], [5,2], [2,4], [5,4], [5,2,4]
After union our bitset is 101011110101





With the advantage of bitset, the inner loop of traversing dp, condition check of dp[j] and operations on next_dp are all transformed to bitwise shift operation, which is much more efficient.

A tiny example, nums=[2, 3, 5], initial bits is 1, traversing through nums

when num=2, bits=101, which represents nums can sum to 0 and 2
when num=3, bits=101101, which represents nums can sum to 0, 2, 3, 5
when num=5, bits=10110101101, which represents nums can sum to 0, 2, 3, 5, 7, 8, 10
Finally, we just need to check if bits[5] is 0 or 1
*/




// ******* DP Bottom up O(N*N) space *******
// same as 0/1 knapsack
class Solution {
public:
	bool canPartition(vector<int>& n) {
		int sum = accumulate(begin(n), end(n), 0);
		if (sum % 2 == 1) return false;

		int size = n.size(); sum = sum/2;
		bool dp[size+1][sum+1];

		for (int i=0; i <= size; i++) {
			for (int j=0; j <= sum; j++) {
				if (i == 0 && j == 0) dp[i][j] = true;
				else if (i == 0) dp[i][j] = false;
				else if (j == 0) dp[i][j] = true;
				else {
					// pick this ele if it is <= to cur sum
					// or don't pick this element
					bool pick = (j >= n[i-1]) && dp[i-1][j - n[i-1]];
					bool notPick = dp[i-1][j];
					dp[i][j] = pick or notPick;
				}
			}
		}

		return dp[size][sum];
	}
};





// ******* DP Bottom up O(2*N) space *******
// same as 0/1 knapsack
// note that i%2 -> curr row, and (i+1)%2 -> prev row
// bcz only prev row is needed to determine the curr answer
class Solution {
public:
	bool canPartition(vector<int>& n) {
		int sum = accumulate(begin(n), end(n), 0);
		if (sum % 2 == 1) return false;

		int size = n.size(); sum = sum/2;
		bool dp[2][sum+1];

		for (int i=0; i <= size; i++) {
			for (int j=0; j <= sum; j++) {
				if (i == 0 && j == 0) dp[i % 2][j] = true;
				else if (i == 0) dp[i % 2][j] = false;
				else if (j == 0) dp[i % 2][j] = true;
				else {
					// pick this ele if it is <= to cur sum
					// or don't pick this element
					bool pick = (j >= n[i-1]) && dp[(i+1) % 2][j - n[i-1]];
					bool notPick = dp[(i+1) % 2][j];
					dp[i % 2][j] = pick or notPick;
				}
			}
		}

		return dp[size % 2][sum];
	}
};




/* ******* DP Bottom up O(N) space *******
		   same as 0/1 knapsack

In 2D dp solution, as we're only using values from previous row, it can be optimized more in space.
Either using a 2 row dp with mod 2 to access the row index, or by a different method as below.
*/
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int sum = accumulate(begin(nums), end(nums), 0);
		if (sum % 2 == 1) return false;

		int size = nums.size(); sum = sum/2;
		bool dp[sum+1]; memset(dp, 0, sizeof(dp));
		dp[0] = true; // getting zero sum is always true (don't pick any item)

		for (int n : nums) {
			for (int s = sum; s >= n; s--) {
				dp[s] = dp[s] or dp[s-n];
			}
		}

		return dp[sum];
	}
};
/*
**** WHY GO FROM RIGHT TO LEFT FOR SUM ****

The reason is that we have to get dp[i] from its previous loop dp[i-1]

dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]]
As for

for (int num: nums){
   for (int i = sum; i>0; i--){
	  if (i>=num)
		 dp[i] = dp[i] || dp[i-num]
	}
}
Every loop of nums refreshes dp array. We might get dp[i] from dp[i-num] whose index is smaller than i.
If we increase the index of sum from 0 to sum, we will get dp[i] from dp[i-num] ,
while dp[i-num] has been updated in this loop. This dp[i-num] is not the number we got from the previous loop.

So why would we do this? This is because the numbers in nums can only be used once.
If we can choose each number several times, we have to increase i from 0 to sum.
Which means, if we are going to choose dp[i], we have to consider the situation
where dp[i] has been chosen before. In this case, dp[i] is updated from dp[i-num]
which is in the same loop with dp[i].
This dp[i-num] we use is a kind of result where dp[i] has been chosen.


from left to right means dp[i][j] = dp[i][j-nums[i-1]])
form right to left means dp[i][j] = dp[i-1][j-nums[i-1]]
*/


/*
 ************** MUST READ *************
Q). in which situation 2 dimensional DP can be dropped to 1 dimension?
		Is there any principle or regular pattern?


Yes, the magic is observation from the induction rule/recurrence relation!

For this problem, the induction rule:

If not picking nums[i - 1], then dp[i][j] = dp[i-1][j]
if picking nums[i - 1], then dp[i][j] = dp[i - 1][j - nums[i - 1]]
You can see that if you point them out in the matrix, it will be like:

			  j
	. . . . . . . . . . . . 
	. . . . . . . . . . . .  
	. . ? . . ? . . . . . .  ?(left): dp[i - 1][j - nums[i], ?(right): dp[i - 1][j]
i	. . . . . # . . . . . .  # dp[i][j]
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . .

Optimize to O(2*n):
you can see that dp[i][j] only depends on previous row,
so you can optimize the space by only using 2 rows instead of the matrix.
Let's say array1 and array2. Every time you finish updating array2,
array1 have no value, you can copy array2 to array1 as the previous row of the next new row.

Optimize to O(n):
you can also see that, the column indices of dp[i - 1][j - nums[i] and dp[i - 1][j] are <= j.
The conclusion you can get is: the elements of previous row
whose column index is > j(i.e. dp[i - 1][j + 1 : n - 1])
will not affect the update of dp[i][j] since we will not touch them:

			  j
	. . . . . . . . . . . . 
	. . . . . . . . . . . .  
	. . ? . . ? x x x x x x  you will not touch x for dp[i][j]
i	. . . . . # . . . . . .  # dp[i][j]
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . . 
	. . . . . . . . . . . .


Thus if you merge array1 and array2 to a single array array,
if you update array backwards, all dependencies are not touched!

	(n represents new value, i.e. updated)
	. . ? . . ? n n n n n n n
			  #  

However if you update forwards, dp[j - nums[i - 1]] is updated already, you cannot use it:

	(n represents new value, i.e. updated)
	n n n n n ? . . . . . .  where another ? goes? Oops, it is overriden, we lost it :(
			  #

Conclusion:
So the rule is that observe the positions of current element and its dependencies in the matrix.
Mostly if current elements depends on the elements in previous row(most frequent case)/columns,
you can optimize the space.

*/




// ******* momorization *******
class Solution {
public:
	bool canPartition(vector<int>& n) {
		int sum = accumulate(begin(n), end(n), 0);
		if (sum % 2 == 1) return false;
		vector<vector<int>> dp(n.size(), vector<int>(1+sum/2, -1));
		return hasSubset(n, 0, sum/2, dp);
	}
	
	bool hasSubset(vector<int>& n, int start, int sum, vector<vector<int>>& dp) {
		if (start == n.size()) return sum==0;
		if (sum < 0) return false;
		if (dp[start][sum] != -1) return dp[start][sum];

		bool take = hasSubset(n, start+1, sum-n[start], dp);
		bool notTake = hasSubset(n, start+1, sum, dp);

		return dp[start][sum] = (take || notTake);
	}
};

