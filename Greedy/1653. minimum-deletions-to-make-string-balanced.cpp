// https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/

/*
You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced.
s is balanced if there is no pair of indices (i,j)
such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
*/



class Solution {
public:
	int minimumDeletions(string& s) {
		//dp stores number of chars to remove to make s.substring(0, i) valid
		vector<int> dp(s.size()+1);
		int countB = 0;

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'a') {
				// case 1: keep current a. ==> prev chars must be a...a
				// so need to remove all 'b' chars before i, which is bcount
					
				// case 2: remove current a ==> prev chars must be a...ab...b
				// so need to remove current a and whatever makes substring
				// before current i valid which is dp[i];
				dp[i+1] = min(countB, 1 + dp[i]);
			}
			else {
				// since it is always valid to append 'b' if
				// substring before current i is valid, so just copy
				// whatever makes substring before i valid which is dp[i];
				dp[i+1] = dp[i];
				countB++;
			}
		}

		return dp[s.size()];
	}
};



class Solution {
public:
	int minimumDeletions(string& s) {
		int countB = 0, ans = 0;
		for (char& c : s) {
			if (c == 'a') ans = min(1 + ans, countB);
			else countB++;
		}
		return ans;
	}
};






/*
count the number or Bs coming before, and As coming after
and accordingly find the best place
where I can delete all the Bs coming before(or upto it),
and all the As coming after it
*/

class Solution {
public:
	int minimumDeletions(string& s) {
		int size = s.size();
		vector<int> Bs_till_here(size), As_after_it(size);

		for (int i = 0; i < size; i++) {
			if (i == 0) Bs_till_here[i] = (s[i]=='b');
			else Bs_till_here[i] = Bs_till_here[i-1] + (s[i]=='b');
		}

		for (int i = size-2; i >= 0; i--) {
			As_after_it[i] = As_after_it[i+1] + (s[i+1]=='a');
		}

		// find best index to split
		// means -> delete all Bs untill here, and delete all As after it
		int ans = As_after_it[0];
		for (int i = 0; i < size; i++) {
			ans = min(ans, Bs_till_here[i] + As_after_it[i]);
		}
		
		return ans;
	}
};


// same as above method 
// just keep maintaining the counts on the fly

class Solution {
public:
	int minimumDeletions(string& s) {
		int countA = std::count(s.begin(), s.end(), 'a');
		int deletions = countA, countB = 0;

		for (char& c : s) {
			if (c == 'b') countB++;
			else countA--;
			deletions = min(deletions, countA + countB);
		}
		
		return deletions;
	}
};

/*
assume we delete all 'a's, this will definitely work since we will have only character 'b' left - like "bbbbb".
iterate through the string again, try keep each 'a' and delete each 'b' to see how many total operations we need to make the string balanced.
why we can keep each 'a'? since all the 'a's on the right side of the current position are already deleted by step 1. But we need to remember to revert one 'a' deletion back (--as).
why we need to delete each 'b'? since we don't want any 'b' sits on the left side (++bs).
*/