// https://leetcode.com/problems/word-ladder-ii/




// cleaner implementation of second solution (BFS of paths)
class Solution {

public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &List) {

		unordered_set<string> wordList(List.begin(), List.end());
		if (!wordList.count(endWord))
			return vector<vector<string>>();

		vector<vector<string>> result;
		queue<vector<string>> q; // queue contains paths of level length
		q.push({ beginWord });
		int level = 0;
		
		unordered_set<string> visited; // contains words used in current level
		
		while (!q.empty()) {
			//reach a new level, so clear all nodes of prev level
			for (string w : visited)
				wordList.erase(w);
			visited.clear();

			level++;
			int size = q.size();

			while (size--) {
				vector<string> path = q.front(); q.pop();
				string w1 = path.back();

				for (string& w2: getNextWords(w1, wordList)) {
					visited.insert(w2);
					vector<string> newPath = path;
					newPath.push_back(w2);
					if (w2 == endWord)
						result.push_back(newPath);
					else
						q.push(newPath);
				}
			}
		}

		return result;
	}

	vector<string> getNextWords(string& w1, unordered_set<string>& wordList) {
		vector<string> result;
		for (int i = 0; i < w1.size(); ++i) {
			string w2 = w1;
			for (char c = 'a'; c <= 'z'; ++c) {
				w2[i] = c;
				if (w2!=w1 && wordList.count(w2))
					result.push_back(w2);
			}
		}
		return result;
	}
};










class Solution {

public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &List) {
		unordered_set<string> wordList(List.begin(), List.end());
		if (!wordList.count(endWord)) return ans;
		//very interesting problem
		//It can be solved with standard BFS. The tricky idea is doing BFS of paths instead of words!
		//Then the queue becomes a queue of paths.
		vector<vector<string>> ans;
		queue<vector<string>> paths;
		paths.push({beginWord});
		int level = 1;
		int minLevel = INT_MAX;
		
		//"visited" records all the visited nodes on this level
		//these words will never be visited again after this level 
		//and should be removed from wordList. This is guaranteed
		// by the shortest path.
		unordered_set<string> visited;
		
		while (!paths.empty()) {

			vector<string> path = paths.front(); paths.pop();
			
			if (path.size() > level) {
				//reach a new level
				for (string w : visited) wordList.erase(w);
				visited.clear();
				if (path.size() > minLevel)
					break;
				else
					level = path.size();
			}

			string last = path.back();
			//find next words in wordList by changing
			//each element from 'a' to 'z'
			for (int i = 0; i < last.size(); ++i) {
				string news = last;
				for (char c = 'a'; c <= 'z'; ++c) {
					news[i] = c;
					if (wordList.count(news)) {
					//next word is in wordList
					//append this word to path
					//path will be reused in the loop
					//so copy a new path
						vector<string> newpath = path;
						newpath.push_back(news);
						visited.insert(news);
						if (news == endWord) {
							minLevel = level;
							ans.push_back(newpath);
						}
						else
							paths.push(newpath);
					}
				}
			}
		}

		return ans;
	}
};







// Backtracking - TLE
class Solution {
	string end;
	int minPathSize;
	unordered_map<string, bool> dict;
	vector<vector<string>> ans;
	vector<string> cur;
	
public:
	vector<vector<string>> findLadders(string begin, string end, vector<string>& List) {
		this->end = end;
		this->minPathSize = INT_MAX;
		for (auto& w : List) dict[w] = false;
		cur.push_back(begin);
		dict[begin] = true;
		backtrack();
		return ans;
	}
	
	void backtrack() {
		if (cur.back() == end) {
			if (cur.size() < minPathSize)
				minPathSize = cur.size(), ans.clear();
			if (cur.size() == minPathSize)
				ans.push_back(cur);
			return;
		}
		string w = cur.back();
		for (int i = 0; i < w.size(); i++) {
			char origChar = w[i];
			for (char c = 'a'; c <= 'z'; c++) {
				if (c == origChar) continue;
				w[i] = c;
				auto itr = dict.find(w);
				if (itr == dict.end() or itr->second)
					continue;
				itr->second = true;
				cur.push_back(w);
				backtrack();
				cur.pop_back();
				itr->second = false;
			}
			w[i] = origChar;
		}
	}
};
