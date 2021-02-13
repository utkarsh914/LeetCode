// https://leetcode.com/problems/longest-consecutive-sequence/


/*

Then go through the numbers. If the number x is the start of a streak (i.e., x-1 is not in the set),
then test y = x+1, x+2, x+3, ... and stop at the first number y not in the set.
The length of the streak is then simply y-x and we update our global best with that.
Since we check each streak only once, this is overall O(n).
*/
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> s(nums.begin(), nums.end());
		int best = 0;
		for (int n : s) {
			if (s.count(n-1)) // check in increasing direction only
				continue;
			int c = 1, m = n+1;
			while (s.count(m))
				c++, m++;
			best = max(best, c);
		}
		return best;
	}
};

/*
not checking for n-1 because, if n-1 exists, then we must have already checked for it before
*/