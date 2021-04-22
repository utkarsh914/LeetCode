// https://leetcode.com/problems/magnetic-force-between-two-balls/

/*
In universe Earth C-137, Rick discovered a special form of magnetic force
between two balls if they are put in his new invented basket.
Rick has n empty baskets, the ith basket is at position[i],
Morty has m balls and needs to distribute the balls into the baskets
such that the minimum magnetic force between any two balls is maximum.

Rick stated that magnetic force between two different balls
at positions x and y is |x - y|.

Given the integer array position and the integer m.
Return the required force.

 

Example 1:


Input: position = [1,2,3,4,7], m = 3
Output: 3
Explanation: Distributing the 3 balls into baskets 1, 4 and 7
will make the magnetic force between ball pairs [3, 3, 6].
The minimum magnetic force is 3.
We cannot achieve a larger minimum magnetic force than 3.
*/




class Solution {
public:
	int maxDistance(vector<int>& p, int toPlace) {
		sort(p.begin(), p.end());
		int lo = 1, hi = (p.back()-p.front()) / (toPlace-1), ans = 1;

		while (lo <= hi) {
			int mid = lo + (hi - lo) / 2;
			if (isPossible(p, toPlace, mid))
				ans = mid, lo = mid + 1;
			else
				hi = mid - 1;
		}

		return ans;
	}

	// alternative implementation of above function
	// only using lo and hi
	int maxDistance2(vector<int>& p, int toPlace) {
		sort(p.begin(), p.end());
		int lo = 1, hi = (p.back()-p.front()) / (toPlace-1);

		while (lo < hi) {
			int mid = hi - (hi - lo) / 2; // VERY CRUCIAL! SEE NOTE BELOW
			if (isPossible(p, toPlace, mid))
				lo = mid;
			else
				hi = mid - 1;
		}

		return lo;
	}

	bool isPossible(vector<int>& p, int toPlace, int dist) {
		int placed = 1;
		for (int i = 0, j = 1; j < p.size(); j++) {
			if (p[j] - p[i] >= dist) {
				placed++, i = j;
			}
		}
		return placed >= toPlace;
	}
};


/*
========= HOW TO COMPUTE MID =========

1. ***** mid = lo + (hi - lo) / 2 *****

It is biased towards left.
i.e. if lo=1, hi=2, mid=1
It should be used when our desired answer exists on the left side.
i.e. we are minimizing our answer (in an increasing search space)

bcz, when the condition satisfies, we do
	lo = mid
else
	hi = mid-1



2.  ****** mid = hi - (hi - lo) / 2 *****

It is biased towards right.
i.e. if lo=1, hi=2, mid=2
It should be used when our desired answer exists on the right side.
i.e. we are maximizing our answer (in an increasing search space)

bcz, when the condition satisfies, we do
	lo = mid
else
	hi = mid-1
*/