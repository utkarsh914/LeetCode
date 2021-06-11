// https://leetcode.com/problems/median-of-two-sorted-arrays/







/*
------------ BINARY SEARCH O(log (min(n, m))) -----------

perform BS to find the correct partition in array1,
according to it only, partition in array2 is determined


*/
class Solution {
public:
	double findMedianSortedArrays(vector<int>& N1, vector<int>& N2);
	int getMin(vector<int>& n, int index);
	int getMax(vector<int>& n, int index);
};


double Solution::findMedianSortedArrays(vector<int>& N1, vector<int>& N2) {
	if (N1.size() > N2.size()) N1.swap(N2);
	// N1 is smaller vector
	int lo = 0, hi = N1.size();
	int combinedLength = N1.size() + N2.size();
	
	while (lo <= hi) {
		int part1 = (lo + hi) / 2;
		int part2 = (combinedLength + 1) / 2 - part1;
		
		int left1 = getMax(N1, part1);
		int right1 = getMin(N1, part1);
		
		int left2 = getMax(N2, part2);
		int right2 = getMin(N2, part2);
		
		if (left1 <= right2 and right1 >= left2) {
			if (combinedLength % 2 == 0)
				return (max(left1, left2) + min(right1, right2)) / 2.0;
			else
				return max(left1, left2);
		}
		
		if (left1 > right2)
			hi = part1-1;
		else
			lo = part1+1;
	}

	return -1;
}

int Solution::getMax(vector<int>& n, int index) {
	return (index == 0) ? INT_MIN : n[index-1];
}

int Solution::getMin(vector<int>& n, int index) {
	return (index == n.size()) ? INT_MAX : n[index];
}