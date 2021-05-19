// https://leetcode.com/problems/h-index/

/*
Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper, return compute the researcher's h-index.

According to the definition of h-index on Wikipedia: A scientist has an index h if h of their n papers have at least h citations each, and the other n − h papers have no more than h citations each.

If there are several possible values for h, the maximum one is taken as the h-index.

 

Example 1:

Input: citations = [3,0,6,1,5]
Output: 3
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
*/




class Solution {
public:
	int hIndex(vector<int>& c) {
		sort(c.begin(), c.end(), greater<int>());
		
		for (int i = c.size()-1; i >= 0; i--) {
			if (c[i] >= i+1)
				return i+1;
		}
		
		return 0;
	}
};

/*
6 5 3 1 0
3 1 1
*/
	int hIndex(vector<int>& c) {
		vector<int> bucket(1001);
		for (int n : c) bucket[n]++;

		for (int i = bucket.size() - 2; i >= 0; i--) {
			bucket[i] += bucket[i+1];
		}
		
		for (int i = bucket.size()-1; i >= 0; i--) {
			if (bucket[i] >= i)
				return i;
		}
		
		return 0;
	}