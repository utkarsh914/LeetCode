// https://leetcode.com/problems/longest-word-in-dictionary/

class Solution {

class Trie {
public:
	bool isComplete;
	vector<Trie*> child;
	Trie() { child.resize(26, NULL); isComplete = false; }
};

void insert(Trie* root, string& word) {
	Trie* cur = root;
	for (char c : word) {
		if (!cur->child[c-'a'])
			cur->child[c-'a'] = new Trie();
		cur = cur->child[c-'a'];
	}
	cur->isComplete = true;
}

bool checkContinuous(Trie* root, string& word) {
	Trie* cur = root;
	for (char c : word) {
		cur = cur->child[c-'a'];
		if (!cur->isComplete)
			return false;
	}
	return true;
}

public:
	string longestWord(vector<string>& words) {
		// sort by word length in lexicographically dec order
		sort(words.begin(), words.end(), [](auto& w1, auto& w2) {
			// note this line [seq should be 'apply', 'apple', since we'll check from back]
			if (w1.size() == w2.size()) return w1 > w2;
			return w1.size() < w2.size();
		});

		Trie* root = new Trie();
		for (string& word : words) {
			insert(root, word);
		}
		
		for (int i = words.size()-1; i >= 0; i--) {
			if (checkContinuous(root, words[i]))
				return words[i];
		}
		
		return "";
	}
};








class Solution {
public:
	string longestWord(vector<string>& words) {
		answer = "";
		unordered_set set(words.begin(), words.end());

		for (string& word : words) {
			bool continuous = true;
			string cur = "";

			for (char c : word) {
				cur.push_back(c);
				if (!set.count(cur)) {
					continuous = false;
					break;
				}
			}

			if (continuous and word.size() >= answer.size()) {
				if (word.size() > answer.size() or word < answer)
					answer = word;
			}
		}

		return answer;
	}
}