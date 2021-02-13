// https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/


// basically we need to find minimum sum subarray of size p.size()-k

// ********** using sliding window *********
class Solution {
public:
	int maxScore(vector<int>& p, int k) {
		int totalSum = 0, windowSum = 0, minWindow = INT_MAX;
		int windowSize = p.size()-k;
		// find first window sum
		for (int i=0; i<windowSize; i++)
			totalSum += p[i], windowSum += p[i];
		minWindow = windowSum;

		for (int i=1, j=windowSize; j < p.size(); i++, j++) {
			totalSum += p[j];
			windowSum += p[j] - p[i-1];
			minWindow = min(minWindow, windowSum);
		}

		return totalSum - minWindow;
	}
};





// ********** using recursion *********
class Solution {
public:
	int maxScore(vector<int>& points, int k) {
		return collect(points, 0, points.size()-1, k);
	}
	
	int collect(vector<int>& p, int start, int end, int k) {
		if (k==0) return 0;
		int front = p[start] + collect(p, start+1, end, k-1);
		int back  = p[end] + collect(p, start, end-1, k-1);
		return max(front, back);
	}
};