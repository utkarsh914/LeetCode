// https://leetcode.com/problems/search-suggestions-system/

/*
Given an array of strings products and a string searchWord. We want to design a system that
suggests at most three product names from products after each character of searchWord is typed.
Suggested products should have common prefix with the searchWord.
If there are more than three products with a common prefix return the three lexicographically minimums products.

Return list of lists of the suggested products after each character of searchWord is typed. 

Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
Explanation:
products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
*/



// using binary search
/*

*/
class Solution {
public:
	vector<vector<string>> suggestedProducts(vector<string>& A, string searchWord) {
		auto it = A.begin();
		sort(it, A.end());
		vector<vector<string>> res;
		string cur = "";
		for (char c : searchWord) {
			cur += c;
			vector<string> suggested;
			it = lower_bound(it, A.end(), cur);
			for (int i = 0; i < 3 && it + i != A.end(); i++) {
				string& s = *(it + i);
				if (s.find(cur)) break;
				suggested.push_back(s);
			}
			res.push_back(suggested);
		}
		return res;
	}
};




// using simple sorting
class Solution {
public:
	vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
		int n = searchWord.length();
		vector<vector<string>> res(n,vector<string>());
		sort(products.begin(),products.end());
		
		//first time add all matching first letter 
		int i=0;
		for(string &p: products) {
			if(p[i] == searchWord[i]){
				res[i].push_back(p);
			}
		}
		
		i++;
		while(i < n){
			for(string &item: res[i-1])
			{
				if(item[i]==searchWord[i])
					res[i].push_back(item);
			}
			i++;
		}
		for(int i=0; i < n;i++){
			if(res[i].size()>3)
				res[i].resize(3);
		}
		
		return res;
	}
};




/*
the main idea is to keep storing the words in the trie, that have that prefix.
*/

class Solution {

class Trie {
public:
	vector<Trie*> child;
	vector<string> suggestions;
	Trie() {
		child.resize(26, NULL);
	}
	
	void insert(string& s) {
		Trie* cur = this;
		for (char c : s) {
			if (cur->child[c-'a'] == NULL)
				cur->child[c-'a'] = new Trie();
			cur = cur->child[c-'a'];

			if (cur->suggestions.size() < 3)
				cur->suggestions.push_back(s);
		}
	}
};

public:
	vector<vector<string>> suggestedProducts(vector<string>& products, string& searchWord) {
		sort(products.begin(), products.end());
		Trie* root = new Trie();
		for (auto& p : products)
			root->insert(p);

		return search(root, searchWord);
	}

	vector<vector<string>> search(Trie* root, string& searchWord) {
		vector<vector<string>> ans;
		Trie* cur = root;

		for (char c : searchWord) {
			if (cur != NULL)
				cur = cur->child[c-'a'];
			if (cur == NULL)
				ans.push_back(vector<string>());
			else
				ans.push_back(cur->suggestions);
		}

		return ans;
	}
};
