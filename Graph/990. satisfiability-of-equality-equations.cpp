/*
https://leetcode.com/problems/satisfiability-of-equality-equations/

Given an array equations of strings that represent relationships between variables,
each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".
Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.
Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.

Example 1:
Input: ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.
*/
class Solution {
public:

vector<char> parent;

char find(char x) {
	if (parent[x-'a'] != x)
		parent[x-'a'] = find(parent[x-'a']);
	return parent[x-'a'];
}

void uni(char x, char y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[x-'a'] = y;
	}
}

bool equationsPossible(vector<string>& equations) {
	parent = vector<char> (26);
	for (int i=0; i<26; i++)
		parent[i] = 'a'+i;
	// create unions
	for (auto& eq:equations) {
		if (eq[1]=='=') uni(eq[0], eq[3]);
	}
	// validate unions
	for (auto& eq:equations) {
		if (eq[1]=='=') continue;
		char px=find(eq[0]), py=find(eq[3]);
		if (px==py) return false;
	}
	return true;
}};