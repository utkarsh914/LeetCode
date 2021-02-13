// https://leetcode.com/problems/jump-game/

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
*/

class Solution {
public:
	bool canJump(vector<int>& A) {
		int dist=0;
		for (int i=0; i<=dist; i++) {
			dist = max(dist, A[i]+i);
			if (dist >= A.size()-1)
				return true;
		}
		return false;
	}
};

/*
// *********** LADDER BASED(LIKE JUMP GAME II) **********
class Solution {
public:
	bool canJump(vector<int>& A) {
		if (A.size()==1) return true;
		if (A[0]==0) return false;
		int ladder=A[0], stairs=A[0];
		for (int level=1; level<A.size(); level++) {
			if (level==A.size()-1) return true;
			ladder = max (ladder, level+A[level]);
			stairs--;
			if (stairs==0) stairs=ladder-level;
			// if even after changing the ladder, I don't have any stairs
			// then, can't reach to the end
			if (stairs<=0) return false;
		}
		return true;
	}
};

*/