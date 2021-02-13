/*
https://leetcode.com/problems/similar-string-groups/

Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y. Also two strings X and Y are similar if they are equal.
For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
We are given a list strs of strings where every string in strs is an anagram of every other string in strs. How many groups are there?

Example 1:

Input: strs = ["tars","rats","arts","star"]
Output: 2
*/

// ************* same as find no. of islands ***********
// ********* use union find to group similar str and then count the groups ******
class Solution {
public:

vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[x] = y;
	}
}

int numSimilarGroups(vector<string>& strs) {
	// for union find parent array
	for (int i=0; i<strs.size(); i++) parent.push_back(i);

	for (int i=0; i<strs.size(); i++) {
		for (int j=i+1; j<strs.size(); j++) {
			// test if they are similar
			string& s1=strs[i]; string& s2=strs[j];
			bool hash[s1.length()];
			int mismatch=0;
			for (int k=0; k<s1.length(); k++) {
				hash[k] = s1[k]==s2[k];
				mismatch += !hash[k];
			}
			// if similar, group them
			if (mismatch==0 or mismatch==2)
				uni(i, j);
		}
	}

	// count the number of groups
	vector<int> freq(strs.size(), 0);
	int count=0;
	for (int i=0; i<strs.size(); i++) {
		int p=find(i);
		if (freq[p]==0) count++;
		freq[p]++;
	}
	return count;
	
}};