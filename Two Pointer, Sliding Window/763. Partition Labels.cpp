// https://leetcode.com/problems/partition-labels/

/*
You are given a string s. We want to partition the string into as many parts as possible
so that each letter appears in at most one part.

Return a list of integers representing the size of these parts.

 

Example 1:

Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
Example 2:

Input: s = "eccbbbbdec"
Output: [10]
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
*/








/*
use two ptr technique
j is at the last index of a[i]
and when i == j, one part has ended
*/
class Solution {
public:
	vector<int> partitionLabels(string& s) {
		int lastInd[128] = {};
		for (int i = 0; i < s.size(); i++)
			lastInd[s[i]] = i;

		vector<int> ans;
		int last = -1;
		for (int i = 0, j = 0; i < s.size(); i++) {
			j = max(j, lastInd[s[i]]);
			if (i == j) {
				ans.push_back(i - last); // length of current part
				last = i;
			}
		}

		return ans;
	}
};