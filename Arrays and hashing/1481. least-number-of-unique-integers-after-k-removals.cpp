// https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/

/*
Given an array of integers arr and an integer k.
Find the least number of unique integers after removing exactly k elements.

Example 1:

Input: arr = [5,5,4], k = 1
Output: 1
Explanation: Remove the single 4, only 5 is left.
Example 2:
Input: arr = [4,3,1,1,3,3,2], k = 3
Output: 2
Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.
*/




/*
remove k elements having least frequency
*/
class Solution {
public:
	int findLeastNumOfUniqueInts(vector<int>& A, int k) {
		unordered_map<int, int> m;
		for (int& n : A) m[n]++;
		// Only store freq
		vector<int> v; v.reserve(m.size());
		for (auto& p : m) v.push_back(p.second);
		// sort by freq.
		sort(v.begin(), v.end());
		int i = 0;
		while (i < v.size() && k >= v[i]) {
			k -= v[i];
			i++;
		}

		return v.size() - i;
	}
};






/*
same as above
USE BUCKET SORT
*/
class Solution {
public:
	int findLeastNumOfUniqueInts(vector<int>& A, int k) {
		unordered_map<int, int> m;
		for (int& n : A) m[n]++;
		// store freq count in their buckets
		// ith bucket contains the number of ele that have freq i
		vector<int> bucket(A.size()+1, 0);
		for (auto& p : m)
			bucket[p.second]++;
		
		int total = m.size();
		for (int i = 1; i < bucket.size() && k > 0; i++) {
			if (bucket[i] == 0) continue;
			if (k >= bucket[i] * i) { // if possible to remove all ele in bucket
				k -= bucket[i] * i;
				total -= bucket[i];
			} else {
				total -= k / i; // remove whatever no of ele can be removed
				break; // or k = 0; k should become 0 after this step
			}
		}

		return total;
	}
};








/*
Count numbers using a hash map.
Then put the counts to a min heap.
Remove elements from the min heap while k > 0.

The reason we want to use a min heap is that it takes O(m) to build it
(where m is the number of unique elements).
Then, it takes O(log m) to pull a single element.
If we end up pulling i elements, it will take O(i log m).
*/
int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
	unordered_map<int, int> counts;
	vector<int> heap;
	for (auto n : arr)
		++counts[n];
	for (auto &p: counts)
		heap.push_back(p.second);
	make_heap(begin(heap), end(heap), greater<int>());
	while (k > 0) {
		k -= heap.front();
		pop_heap(begin(heap), end(heap), greater<int>()); 
		if (k >= 0)
			heap.pop_back();
	}
	return heap.size();
}