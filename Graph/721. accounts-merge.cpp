/*
https://leetcode.com/problems/accounts-merge/

Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name,
and the rest of the elements are emails representing emails of the account.
Now, we would like to merge these accounts. Two accounts definitely belong to the same person
if there is some email that is common to both accounts. Note that even if two accounts have the same name,
they may belong to different people as people could have the same name.
A person can have any number of accounts initially, but all of their accounts definitely have the same name.
After merging the accounts, return the accounts in the following format:
the first element of each account is the name, and the rest of the elements are emails in sorted order.
The accounts themselves can be returned in any order.

Example 1:
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
*/

class Solution {
public:

unordered_map <string, string> parent;
unordered_map <string, string> owner;
unordered_map <string, set<string>> unions;

string find(string x) {
	if (!parent.count(x))
		return parent[x] = x;
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(string x, string y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[y] = x;
	}
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
	int n = accounts.size();
	// set parents to self, and set owners
	// we'll need to find owners of representatives only, so store ownsrs only for a[1]
	for (auto& a:accounts) {
		owner[a[1]] = a[0];
		for (int i=1; i<a.size(); i++)
			parent[a[i]] = a[i];
	}
	// create unions
	for (auto& a:accounts) {
		for (int i=1; i<a.size(); i++) {
			uni(a[1], a[i]);
		}
	}
	// map unions to representatives(parents)
	for (auto& a:accounts) {
		for (int i=1; i<a.size(); i++) {
			unions[find(a[i])].insert(a[i]);
		}
	}
	// create output
	vector<vector<string>> result;
	for (auto& u:unions) {
		vector<string> emails;
		emails.push_back(owner[u.first]);
		for (auto& e:u.second)
			emails.push_back(e);
		result.push_back(emails);
	}

	return result;
}};