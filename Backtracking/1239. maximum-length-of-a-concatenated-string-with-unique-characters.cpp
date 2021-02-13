/*
https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

Given an array of strings arr. String s is a concatenation of a sub-sequence of arr which have unique characters.
Return the maximum possible length of s.

Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
Maximum length is 4.

*/



// ********** DFS (16 ms) **********
class Solution {
public:

	int maxLengthAns = 0;

	int maxLength(vector<string>& arr) {
		dfs(arr, "", 0);
		return maxLengthAns;
	}

	void dfs(vector<string>& arr, string curr, int start) {
		bool unique = isUnique(curr);
		if (unique && curr.length()>maxLengthAns) maxLengthAns = curr.length();
		if (!unique or start==arr.size()) return;
		for (int i=start; i<arr.size(); i++)
			dfs(arr, curr+arr[i], i+1);
	}

	bool isUnique(string& s) {
		int hash[26] = {0};
		for (auto i:s) {
			if (hash[i-'a'] != 0)
				return false;
			hash[i-'a']++;
		}
		return true;
	}
};




// ********** DFS (memorized) (SLOWER than dfs) **********
class Solution {
public:

	unordered_map<string, int> dp;

	int maxLength(vector<string>& arr) {
		int maxLengthAns = 0;
		return dfs(arr, "", 0, maxLengthAns);
	}

	int dfs(vector<string>& arr, string curr, int start, int maxLengthAns) {
		if (dp.count(curr)) return dp[curr];
		bool unique = isUnique(curr);
		if (unique && curr.length()>maxLengthAns) maxLengthAns = curr.length();
		if (!unique or start==arr.size()) {
			dp[curr] = maxLengthAns;
			return maxLengthAns;
		}
		for (int i=start; i<arr.size(); i++)
			maxLengthAns = dfs(arr, curr+arr[i], i+1, maxLengthAns);
		dp[curr] = maxLengthAns;
		return maxLengthAns;
	}

	bool isUnique(string& s) {
		int hash[26] = {0};
		for (auto i:s) {
			if (hash[i-'a'] != 0)
				return false;
			hash[i-'a']++;
		}
		return true;
	}
};






// ********** BACKTRACKING (TLE) **********
class Solution {
public:

	int maxLengthAns = 0;
	int currCount = 0;
	vector<int> hash;

	int maxLength(vector<string>& arr) {
		hash = vector<int>(26, 0);
		backtrack(arr, 0);
		return maxLengthAns;
	}

	void backtrack(vector<string>& arr, int start) {
		maxLengthAns = max(maxLengthAns, currCount);
		for (int i=start; i<arr.size(); i++) {
			bool pushed = true;
			// if not unique, set flag to false
			for (auto j:arr[i])
				if (hash[j-'a'] != 0) pushed=false;
			// if unique, update hash array
			if (pushed) {
				currCount += arr[i].length();
				for (auto j:arr[i])
					hash[j-'a'] = 1;
			}
			// backtrack on remaining part
			backtrack(arr, start+1);
			// if pushed, now remove it from hash
			if (pushed) {
				currCount -= arr[i].length();
				for (auto j:arr[i])
					hash[j-'a'] = 0;
			}
		}
	}
};




