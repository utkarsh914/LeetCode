// https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/

/*
Given the array favoriteCompanies where favoriteCompanies[i] is the list of favorites companies for the ith person (indexed from 0).

Return the indices of people whose list of favorite companies is not a subset of any other list of favorites companies. You must return the indices in increasing order.

 

Example 1:

Input: favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
Output: [0,1,4] 
Explanation: 
Person with index=2 has favoriteCompanies[2]=["google","facebook"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] corresponding to the person with index 0. 
Person with index=3 has favoriteCompanies[3]=["google"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] and favoriteCompanies[1]=["google","microsoft"]. 
Other lists of favorite companies are not a subset of another list, therefore, the answer is [0,1,4].
*/



/*
1. Use hashing to convert company names in numbers
and then for each list check if this is a subset of any other list.

2. In order to check if a list is a subset of another list,
use two pointers technique to get a linear solution for this task.
The total complexity will be O(n^2 * m)
where n is the number of lists and m is the maximum number of elements in a list.
*/
class Solution {
public:
	vector<int> peopleIndexes(vector<vector<string>>& Companies) {
		hash<string> myhash;
		vector<vector<int>> C;

		for (auto& v : Companies) {
			vector<int> temp;
			for (auto& s : v)
				temp.push_back(myhash(s));
			C.emplace_back(temp);
		}

		vector<int> ans;
		for (int i = 0; i < C.size(); i++) {
			bool to_push = true;
			for (int j = 0; j < C.size(); j++) {
				if (i == j) continue;
				if (isSubset(C[i], C[j])) {
					to_push = false;
					break;
				}
			}
			if (to_push) ans.push_back(i);
		}

		return ans;
	}

	bool isSubset(vector<int>& A, vector<int>& B) {
		int i = 0, j = 0;
		while (i < A.size() and j < B.size()) {
			if (A[i] == B[j]) i++;
			j++;
		}
		return i == A.size();
	}
};





// ****** using BITSET ******
class Solution {
public:
	vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
		unordered_map<string, int> m;
		int id = 1, sz = favoriteCompanies.size();
		
		for (const auto &fc: favoriteCompanies) {
			for (const auto &c: fc) {
				if (m.count(c) > 0) continue;
				m[c] = id++;
			}
		}
		
		vector<bitset<50001>> vec;
		for (const auto &fc: favoriteCompanies) {
			bitset<50001> b;
			for (const auto &c: fc) {
				b[m[c]] = 1;
			}
			vec.push_back(b);
		}
		
		vector<int> res;
		for (int i = 0; i < sz; ++i) {
			bool flag = true;
			for (int j = 0; j < sz and flag; ++j) {
				if (i == j) continue;
				if ((vec[i] & vec[j]) == vec[i]) flag = false;
			}
			if (flag) res.push_back(i);
		}
		
		return res;
	}
};