// https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/



class Solution {
public:
	bool hasAllCodes(string& s, int k) {
		if (k > 15) return false;

		int total = 1 << k;
		vector<bool> set(total, false);
		
		int n = stoi(s.substr(0,k), 0, 2);

		for (int i=k; i <= s.size(); i++) {
			// check prev window
			set[n] = true;
			if (i == s.size()) break;
			// create current window
			n = n & ~(1 << (k-1)); // clear kth bit (or MSB)
			n = (n << 1) | (s[i]-'0'); // set curr bit (or LSB)
		}
		
		// check if all the possible combinations are found
		for (bool b : set)
			if (b == false)
				return false;
		return true;
	}
	
};

/*
with k = 20, we need to have 1,048,576 different numbers,
which is impossibleif the input string size is limited to 5 * 10^5.
We need at least 1,048,576 multiplied by some average gap -
it's impossible for all numbers to share 19 characters.
*/




class Solution {
public:
	bool hasAllCodes(string& s, int k) {
		
		unordered_set<string> set;
		
		for (int i=0; i < (1<<k); i++) {
			string temp;
			for (int j=k-1; j>=0; j--) {
				char c = i & (1<<j) ? '1' : '0';
				temp.push_back(c);
			}
			set.insert(temp);
		}
		
		string temp = s.substr(0,k);
		for (int i=k; i <= s.size(); i++) {
			// check prev window
			if (set.count(temp)) set.erase(temp);
			if (i == s.size()) break;
			temp.erase(temp.begin()); temp.push_back(s[i]);
		}
		
		return set.size()==0;
	}
	
};