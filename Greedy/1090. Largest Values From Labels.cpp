// https://leetcode.com/problems/largest-values-from-labels/

/*
We have a set of items: the i-th item has value values[i] and label labels[i].

Then, we choose a subset S of these items, such that:

|S| <= num_wanted
For every label L, the number of items in S with label L is <= use_limit.
Return the largest possible sum of the subset S.

 

Example 1:

Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], num_wanted = 3, use_limit = 1
Output: 9
Explanation: The subset chosen is the first, third, and fifth item.
Example 2:

Input: values = [5,4,3,2,1], labels = [1,3,3,3,2], num_wanted = 3, use_limit = 2
Output: 12
Explanation: The subset chosen is the first, second, and third item.
*/













/*
Sort all labels by value.
Then, start with the largest value,greedily pick labels.
Track how many labels we have used in m,
and do not pick that label if we reached the limit.
*/
class Solution {
public:
	int largestValsFromLabels(vector<int>& V, vector<int>& L,
		int num_wanted, int use_limit) {
		
		unordered_map<int, int> map;
		priority_queue<array<int,2>> pq;
		for (int i = 0; i < V.size(); i++)
			pq.push({ V[i], L[i] });

		int sum = 0, taken = 0;
		while (!pq.empty() and taken < num_wanted) {
			auto cur = pq.top(); pq.pop();
			if (map[cur[1]] < use_limit) {
				map[cur[1]]++;
				sum += cur[0];
				taken++;
			}
		}

		return sum;
	}
};