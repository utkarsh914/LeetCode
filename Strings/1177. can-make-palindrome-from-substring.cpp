// https://leetcode.com/problems/can-make-palindrome-from-substring/

/*
Given a string s, we make queries on substrings of s.

For each query queries[i] = [left, right, k],
we may rearrange the substring s[left], ..., s[right],
and then choose up to k of them to replace with any lowercase English letter. 

If the substring is possible to be a palindrome string after the operations above,
the result of the query is true. Otherwise, the result is false.

Return an array answer[], where answer[i] is the result of the i-th query queries[i].

Note that: Each letter is counted individually for replacement
so if for example s[left..right] = "aaa", and k = 2, we can only replace two of the letters.
(Also, note that the initial string s is never modified by any query.)


Example :

Input: s = "abcda", queries = [[3,3,0],[1,2,0],[0,3,1],[0,3,2],[0,4,1]]
Output: [true,false,false,true,true]
Explanation:
queries[0] : substring = "d", is palidrome.
queries[1] : substring = "bc", is not palidrome.
queries[2] : substring = "abcd", is not palidrome after replacing only 1 character.
queries[3] : substring = "abcd", could be changed to "abba" which is palidrome.
	Also this can be changed to "baab" first rearrange it "bacd" then replace "cd" with "ab".
queries[4] : substring = "abcda", could be changed to "abcba" which is palidrome.
 

Constraints:

1 <= s.length, queries.length <= 10^5
0 <= queries[i][0] <= queries[i][1] < s.length
0 <= queries[i][2] <= s.length
s only contains lowercase English letters.
*/






/*
Method 1: prefix sum - count each char
*/
class Solution {
	vector<vector<int>> f;
public:
	vector<bool> canMakePaliQueries(string& s, vector<vector<int>>& queries) {
		calculatePreFreq(s);
		vector<bool> ans(queries.size());

		for (int i = 0; i < queries.size(); i++) {
			auto& q = queries[i];
			vector<int> freq = preFreq(q[0], q[1]);
			int odds = 0;
			for (int x : freq) odds += x%2;
			/*
			odds -= 2*q[2]; // 1 replacemnt removes 2 odd freq (makes them even)
			if ((q[1]-q[0]+1) % 2 == 1) // only if length is odd, 1 odd freq is allowed
				odds--;
			ans[i] = odds <= 0; // remaining odds should be <= 0 after replacement
			*/
			ans[i] = q[2] >= odds/2;
		}

		return ans;
	}

	void calculatePreFreq(string& s) {
		f.push_back(vector<int> (26, 0));
		f.push_back(vector<int> (26, 0));
		// first char of string
		f[1][s[0]-'a']++;
		for (int i = 1; i < s.size(); i++) {
			f.push_back(f[i]);
			f[i+1][s[i]-'a']++;
		}
	}

	vector<int> preFreq(int i, int j) {
		vector<int> ans = f[j+1];
		for (int k=0; k < 26; k++)
			ans[k] -= f[i][k];
		return ans;
	}
};








/*
Method 1: CLEANER
*/
class Solution {
public:
	vector<bool> canMakePaliQueries(string& s, vector<vector<int>>& queries) {
		vector<vector<int>> f(s.size()+1, vector<int>(26,0));
		// compute prefix freq
		for (int i = 0; i < s.size(); i++) {
			f[i+1] = f[i]; // clone prev array
			f[i+1][s[i]-'a']++;
		}

		vector<bool> ans(queries.size());

		for (int i = 0; i < queries.size(); i++) {
			int start = queries[i][0], end = queries[i][1];
			int odds = 0, maxReplace = queries[i][2];
			for (int j = 0; j < 26; j++)
				odds += (f[end+1][j] - f[start][j]) % 2;
			ans[i] = maxReplace >= odds/2;
		}

		return ans;
	}
};








/*
Method 2: USE BOOL TO STORE IF FREQ IS ODD
*/
class Solution {
public:
	vector<bool> canMakePaliQueries(string& s, vector<vector<int>>& queries) {
		vector<vector<bool>> isOdd(s.size()+1, vector<bool>(26, false));
		// compute prefix freq
		for (int i = 0; i < s.size(); i++) {
			isOdd[i+1] = isOdd[i]; // clone prev array
			isOdd[i+1][s[i]-'a'] = !isOdd[i+1][s[i]-'a'];
		}

		vector<bool> ans(queries.size());

		for (int i = 0; i < queries.size(); i++) {
			int start = queries[i][0], end = queries[i][1];
			int odds = 0, maxReplace = queries[i][2];
			for (int j = 0; j < 26; j++)
				odds += (isOdd[end+1][j] ^ isOdd[start][j]) ? 1 : 0;
			ans[i] = maxReplace >= odds/2;
		}

		return ans;
	}
};







/*
Method 3: PREFIX XOR
	use integer bit 0/1 to mark the even/odd of the count of each char
*/
class Solution {
public:
	vector<bool> canMakePaliQueries(string& s, vector<vector<int>>& queries) {
		vector<int> isOdd(s.size()+1);
		// compute prefix freq
		for (int i = 0; i < s.size(); i++) {
			int pos = s[i]-'a'; // revert pos bit in isOdd[i]
			isOdd[i+1] = isOdd[i] ^ (1 << pos);
		}

		vector<bool> ans(queries.size());

		for (int i = 0; i < queries.size(); i++) {
			int start = queries[i][0], end = queries[i][1], maxReplace = queries[i][2];
			/*
			int odds = 0;
			for (int j = 0; j < 26; j++)
				odds += ((isOdd[end+1] & (1<<j)) ^ (isOdd[start] & (1<<j))) ? 1 : 0;
			*/
			int odds = __builtin_popcount(isOdd[end+1] ^ isOdd[start]);
			ans[i] = maxReplace >= odds/2;
		}

		return ans;
	}
};