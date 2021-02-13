// https://leetcode.com/problems/find-all-anagrams-in-a-string/

// exactly same as: 567. permutations in string

class Solution {
public:
	vector<int> findAnagrams(string& s2, string& s1) {
		int len1 = s1.length(), len2 = s2.length();
		if (len1 > len2) return vector<int>();
		
		vector<int> count(26, 0), ans;
		for (int i = 0; i < len1; i++) {
			count[s1[i] - 'a']++;
			count[s2[i] - 'a']--;
		}
		if (allZero(count))
			ans.push_back(0);
		
		for (int i = len1; i < len2; i++) {
			count[s2[i] - 'a']--;
			count[s2[i - len1] - 'a']++;
			if (allZero(count))
				ans.push_back(i-len1+1);
		}
		
		return ans;
	}
	
	bool allZero(vector<int>& count) {
		for (int i = 0; i < 26; i++) {
			if (count[i] != 0) return false;
		}
		return true;
	}
};