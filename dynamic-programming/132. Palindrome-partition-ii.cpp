/*
https://leetcode.com/problems/palindrome-partitioning-ii/

Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1
*/

class Solution {
public:
	int minCut(string s);
};

int Solution::minCut(string s) {
	int l = s.length();
	bool pal[l][l];
	int dp[l];
	
	// fill ispalindrome table
	for (int len=1; len<=l; len++) {
		int i=0, j=i+len-1;
		if (len==1) {
			while (i<l) pal[i][i]=true, i++;
		}
		else if (len==2) {
			while (j<l) {
				pal[i][j] = (s[i]==s[j]);
				i++, j++;
			}
		}
		else {
			while (j<l) {
				pal[i][j] = (s[i]==s[j]) ? pal[i+1][j-1] : false;
				i++, j++;
			}
		}
	}
	
	// find min cuts now
	
	for (int i=l-1; i>=0; i--) {
		if (pal[i][l-1]) {
			dp[i]=0;
			continue;
		}
		int temp=l-i-1;
		int j=i;
		while (j<l-1) {
			if (pal[i][j]) temp = min(temp, 1+dp[j+1]);
			j++;
		}
		dp[i]=temp;
	}
	
	return dp[0];
} 


// ******* SLOWER *********
class Solution {
public:
	vector<int> dp;
	int minCut(string s) {
		dp = vector<int> (s.length(), -1);
		return partition(s, 0);
	}

	int partition(string& s, int start) {
		if (start>=s.length()) return s.length()-1;
		if (dp[start] != -1) return dp[start];
		
		bool ispal = true;
		int lo=start, hi=s.length()-1;
		while (lo<hi) {
			if (s[lo] != s[hi]) {ispal=false; break;}
			lo++, hi--;
		}
		if (ispal) return dp[start]=0;
		
		int ans = s.length()-start-1;
		for (int i=start; i<s.length(); i++) {
			bool ispal = true;
			int lo=start, hi=i;
			while (lo<hi) {
				if (s[lo] != s[hi]) {ispal=false; break;}
				lo++, hi--;
			}
			if (ispal) ans = min(ans, 1+partition(s,i+1));
		}
		return dp[start]=ans;
	}
};