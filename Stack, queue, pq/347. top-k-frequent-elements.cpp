// https://leetcode.com/problems/top-k-frequent-elements/

class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int,int> f;
		for (int n:nums) f[n]++;
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
		for (auto& p:f) {
			pq.push({p.second, p.first});
			if (pq.size() > k) pq.pop();
		}
		vector<int> result;
		while (!pq.empty())
			result.push_back(pq.top().second), pq.pop();
		return result;
	}
};





// using bucket sort 
// Build a array of list to be buckets with length 1 to sort.
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		// get frequencies of all elements
		unordered_map<int,int> f;
		for (int n:nums) f[n]++;

		// max freq of an element can be the array size
		vector<vector<int>> buckets(nums.size()+1);

		for (auto& p:f) {
			buckets[p.second].push_back(p.first);
		}

		vector<int> result;
		for (int i=buckets.size()-1; i>=0 && result.size() < k; i--) {
			for (int n:buckets[i])
				result.push_back(n);
		}

		return result;
	}
};