// https://leetcode.com/problems/longest-happy-string/

class Solution {
public:
	string longestDiverseString(int a, int b, int c) {
		priority_queue<pair<int,char>> pq;
		if (a > 0) pq.push({a,'a'});
		if (b > 0) pq.push({b,'b'});
		if (c > 0) pq.push({c,'c'});
		
		string s;
		
		while (!pq.empty()) {
			auto cur1 = pq.top(); pq.pop();
			int l = s.length();	char ch = cur1.second;
			if (l >= 2 and s[l-1]==ch and s[l-2]==ch) {
				if (pq.empty()) return s;
				auto cur2 = pq.top(); pq.pop();
				s += cur2.second;
				if (--cur2.first > 0) pq.push(cur2);
				pq.push(cur1);
			}
			else {
				s += ch;
				if (--cur1.first > 0) pq.push(cur1);
			}
		}
		
		return s;
	}
};