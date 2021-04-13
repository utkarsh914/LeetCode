// https://leetcode.com/problems/concatenated-words/

/*
Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example 1:

Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
*/

// =========== TLE ==========
class Solution {
	vector<string> ans;

	class Trie {
	public:
		vector<Trie*> child;
		bool complete;
		Trie() { child.resize(26, NULL); complete=false;}
	};

	void insert(Trie* root, string& w) {
		if (isPresent(root, w, 0))
			this->ans.push_back(w);

		Trie* cur = root;
		for (int i=0; i < w.length(); i++) {
			char& c = w[i];
			if (!cur->child[c-'a'])
				cur->child[c-'a'] = new Trie();
			cur = cur->child[c-'a'];
		}
		cur->complete = true;
	}

	bool isPresent(Trie* root, string& w, int start) {
		Trie* cur = root;
		for (int i=start; i < w.length(); i++) {
			char& c = w[i];
			if (!cur->child[c-'a'])
				return false;
			cur = cur->child[c-'a'];
			if (cur->complete && isPresent(root, w, i+1))
				return true;
		}
		return true;
	}

public:
	vector<string> findAllConcatenatedWordsInADict(vector<string>& w) {
		this->ans.clear();
		sort(w.begin(), w.end(), [](auto& w1, auto& w2) {
			return w1.length() < w2.length();
		});

		Trie* T = new Trie();
		for (string& s : w)
			insert(T, s);

		return this->ans;
	}
};











// ============== ACCEPTED ============
public class Solution {
	public static List<String> findAllConcatenatedWordsInADict(String[] words) {
		List<String> result = new ArrayList<>();
		Set<String> preWords = new HashSet<>();
		Arrays.sort(words, (w1, w2) -> (w1.length() - w2.length()));
		
		for (int i = 0; i < words.length; i++) {
			if (canForm(words[i], preWords))
				result.add(words[i]);
			preWords.add(words[i]);
		}
		
		return result;
	}
	
	private static boolean canForm(String word, Set<String> dict) {
		if (dict.isEmpty()) return false;
		boolean[] dp = new boolean[word.length() + 1];
		dp[0] = true;
		for (int i = 1; i <= word.length(); i++) {
			for (int j = 0; j < i; j++) {
				if (dp[j] && dict.contains(word.substring(j, i))) {
					dp[i] = true;	break;
				}
			}
		}
		return dp[word.length()];
	}
}