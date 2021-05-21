// https://leetcode.com/problems/string-compression/

class Solution {
public:
	int compress(vector<char>& chars) {
		int g = 1, j = 0;
		char c = chars[0];

		for (int i = 1; i <= chars.size(); i++) {
			char cur = 'a', prev = 'a';

			if (i == chars.size() or chars[i] != chars[i-1]) {
				if (i < chars.size())
					cur = chars[i], prev = chars[i-1];
				
				chars[j++] = c;
				if (g > 1) {
					string gString = to_string(g);
					for (int k = 0; k < gString.size(); k++)
						chars[j++] = gString[k];
				}
			}

			if (i == chars.size()) break;

			if (cur == prev) g++;
			else g = 1, c = chars[i]; // reset group and c
		}

		return j;
	}
};






class Solution {
public:
	int compress(vector<char>& chars) {
		int i = 0, j = 0;

		while (i < chars.size()) {
			char c = chars[i];
			int gsize = 0;
			// count group size
			while (i < chars.size() and chars[i] == c)
				gsize++, i++;
			// set this group details in beginning of string
			chars[j++] = c;
			if (gsize > 1) {
				string gString = to_string(gsize);
				for (int k = 0; k < gString.size(); k++)
					chars[j++] = gString[k];
			}
		}

		return j;
	}
};