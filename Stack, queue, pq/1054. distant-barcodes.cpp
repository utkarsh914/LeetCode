// https://leetcode.com/problems/distant-barcodes/

class Solution {
public:
	vector<int> rearrangeBarcodes(vector<int>& b) {

		multiset<pair<int,int>> s;

		int freq[10001] = {};
		for (int n:b) freq[n]++;

		for (int i=0; i<=10000; i++)
			if (freq[i] > 0)
				s.insert({freq[i], i});

		vector<int> ans(b.size());
		
		for (int i=0; i<b.size(); i+=2) {
			// pick elements with max freq, and min freq
			auto itr1 = --s.end(), itr2 = s.begin();

			ans[i] = itr1->second; // pick ele with max freq
			if (i+1 < b.size()) ans[i+1] = itr2->second; // pick ele with min freq
			
			// reinsert those picked elements with reduced freq
			if (itr1->first > 1)
				s.insert({itr1->first-1, itr1->second});
			if (itr2->first > 1 && i+1 < b.size())
				s.insert({itr2->first-1, itr2->second});
			
			// erase those picked elements
			s.erase(itr1);
			if (i+1 < b.size())	s.erase(itr2);
			

		}

		return ans;
	}
};








class Solution {
public:
	vector<int> rearrangeBarcodes(vector<int>& v) {

		unordered_map<int,int> m;
		priority_queue<pair<int,int>> pq;
		int n = v.size();
		for(int i=0; i<n; i++) m[v[i]]++;
		
		for(auto& p:m) pq.push({p.second, p.first});
		
		vector<int> ans(n,0);
		int pos = 0;

		while(!pq.empty()){
			int fr = pq.top().first;
			int val = pq.top().second;
			pq.pop();
			while(fr--){
				ans[pos] = val;
				 pos = n > pos + 2 ? pos + 2 : 1;
			}
		}

		return ans;
	}
};







/*
Like Jianwen observed below, we do not need to sort elements by the number of occurrences,
we just need to determine the most frequent one and fill it first. The rest of barcodes can be filled
irrespective of their occurrences. Note that you still fill all occurrences of the same barcode
skipping a position before moving to the next barcode.
Since barcodes are limited to [1...10000], we can use an array instead of hash map to make it even faster.
*/
class Solution {
public:
	vector<int> rearrangeBarcodes(vector<int>& b) {
		short m[10001] = {};
		short max_cnt = 0, max_n = 0, pos = 0;
		for (auto n : b) {
			max_cnt = max(max_cnt, ++m[n]);
			max_n = max_cnt == m[n] ? n : max_n;
		}
		for (auto i = 0; i <= 10000; ++i) {
			auto n = i == 0 ? max_n : i;
			while (m[n]-- > 0) {
				b[pos] = n;
				pos = pos + 2 < b.size() ? pos + 2 : 1;
			}
		}
		return b;
	}
};