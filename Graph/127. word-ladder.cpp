// https://leetcode.com/problems/word-ladder/

/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words such that:

The first word in the sequence is beginWord.
The last word in the sequence is endWord.
Only one letter is different between each adjacent pair of words in the sequence.
Every word in the sequence is in wordList.
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog" with 5 words.
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no possible transformation.
*/






// ******** BFS (assume there is an edge to the word that has one letter diff)
// and run dfs to find the end word from beginWord
// *********** slow runtime (700 ms) *************

class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& List) {

		unordered_map<string, bool> vis;
		for (string& w:List) vis[w]=false;
		if (!vis.count(endWord)) return 0;

		int steps = 0;
		queue<string> q;
		q.push(beginWord);

		while (!q.empty()) {
			int size = q.size();
			steps++;
			while (size--) {
				string w1 = q.front(); q.pop();
				if (w1 == endWord) return steps;
				for (string& w2: getNextWords(w1, List, vis)) {
					q.push(w2);
					vis[w2] = true;
				}
			}
		}

		return 0;
	}

	vector<string> getNextWords(string& w1, vector<string>& List, unordered_map<string, bool>& vis) {
		vector<string> result;
		for (string& w2:List) {
			if (hasOneDiff(w1, w2) && !vis[w2])
				result.push_back(w2);
		}
		return result;
	}

	bool hasOneDiff(string& w1, string& w2) {
		int diff = 0;
		for (int i=0; i<w1.length(); i++) {
			diff += w1[i]!=w2[i];
		}
		return diff==1;
	}
};







// ************ superfast runtime (36 ms) ***********
/*
The above code starts from a single end beginWord. We may also start from the endWord simultaneously.
Once we meet the same word, we are done. This link provides such a two-end search solution.
I rewrite the code below for better readability. This solution uses two pointers phead and ptail
to switch to the smallerset at each step to save time.
*/
class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

		unordered_set<string> dict(wordList.begin(), wordList.end()), head, tail;
		unordered_set<string> *phead, *ptail;
		if (!dict.count(endWord))
			return 0;

		head.insert(beginWord);
		tail.insert(endWord);
		int ladder = 2;

		while (!head.empty() && !tail.empty()) {

			// head should always have smaller size, o/w swap the ptrs
			if (head.size() < tail.size()) {
				phead = &head; ptail = &tail;
			} else {
				phead = &tail; ptail = &head;
			}

			unordered_set<string> temp;
			for (auto& w: *phead) {
				string word = w;
				for (int i = 0; i < word.size(); i++) {
					char t = word[i];
					for (int j = 0; j < 26; j++) {
						word[i] = 'a' + j;
						if (ptail->count(word)) {
							return ladder;
						}
						if (dict.count(word)) {
							temp.insert(word);
							dict.erase(word);
						}
					}
					word[i] = t;
				}
			}

			ladder++;
			phead->swap(temp);
		}

		return 0;
	}
};









// ********** alternative, it generates all possible words *********
class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		unordered_set<string> dict(wordList.begin(), wordList.end());
		queue<string> todo;
		todo.push(beginWord);
		int ladder = 1;
		while (!todo.empty()) {
			int n = todo.size();
			for (int i = 0; i < n; i++) {
				string word = todo.front();
				todo.pop();
				if (word == endWord) {
					return ladder;
				}
				dict.erase(word);
				for (int j = 0; j < word.size(); j++) {
					char c = word[j];
					for (int k = 0; k < 26; k++) {
						word[j] = 'a' + k;
						if (dict.find(word) != dict.end()) {
							todo.push(word);
						}
					 }
					word[j] = c;
				}
			}
			ladder++;
		}
		return 0;
	}
};