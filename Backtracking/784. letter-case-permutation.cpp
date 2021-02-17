/*
https://leetcode.com/problems/letter-case-permutation/

Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.
Return a list of all possible strings we could create. You can return the output in any order.

Example 1:

Input: S = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]


// ********** APPROACH ********
Image there is a binary tree, we start from the dummy root,
and the left child node means choice 1(append a lower case),
and right child node is choice 2(upper case).
Hence if String here is abc, we have a tree looks like this.
/ \
a A
/ \ /
ab aB Ab AB
/ \ / \ / \ /
abc abC................................
Obviously our goal here will be printing out all leaf nodes,
which we can accomplished by using DFS with backTracking or BFS.
*/


class Solution {
public:
// ********* BACKTRACKING (OR DFS) *********
vector<string> letterCasePermutation(string input) {
	vector<string> result;
	backtrack(result, input, 0);
	return result;
}

void backtrack(vector<string>& result, string& input, int start) {
	if (start==input.length()) {
		result.push_back(input);
		return;
	}
	if (input[start]>='0' && input[start]<='9') {
		backtrack(result, input, start+1);
		return;
	}
	// take small
	input[start] = tolower(input[start]);
	backtrack(result, input, start+1);
	// take capital
	input[start] = toupper(input[start]);
	backtrack(result, input, start+1);
}
};


// ********* BFS *********
vector<string> letterCasePermutation(string input) {
	
	queue<string> q;
	q.push(input);
	int level = 0;

	while (!q.empty()) {
		if (++level > input.length())
			break;
		int size = q.size();
		while (size--) {
			string curr = q.front(); q.pop();
			if (isdigit(input[level-1])) {
				q.push(curr);
				continue;
			}
			curr[level-1] = tolower(curr[level-1]);
			q.push(curr);
			curr[level-1] = toupper(curr[level-1]);
			q.push(curr);
		}
	}

	vector<string> result;
	while (!q.empty()) result.push_back(q.front()), q.pop();
	return result;
}


// ********* RECURSION **********
class Solution {
public:
	vector<string> result;

	vector<string> letterCasePermutation(string s) {
		solve(s, 0, "");
		return result;
	}

	void solve(string& ip, int start, string op) {
		if (start == ip.length())
			result.push_back(op);

		if (isdigit(ip[start])) {
			solve(ip, start+1, op + ip[start]);
		} else {
			solve(ip, start+1, op + (char)tolower(ip[start]));
			solve(ip, start+1, op + (char)toupper(ip[start]));   
		}
	}

};

/* ******* bit manipulation (wrong) *********

vector<string> letterCasePermutation(string s) {
	vector<string> result;
	for (int i=0; i<(1<<s.length()); i++) {
		string temp;
		bool flag = false;
		for (int j=0; j<s.length(); j++) {
			if (s[j]>='0' and s[j]<='9') temp.push_back(s[j]), flag=true;
			else if (i & (1<<j)) temp.push_back(s[j]-32); // capital
			else temp.push_back(s[j]); //small
		}
		result.push_back(temp);
	}
	return result;
}
*/