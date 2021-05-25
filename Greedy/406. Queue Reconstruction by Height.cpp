// https://leetcode.com/problems/queue-reconstruction-by-height/

/*
You are given an array of people, people,
which are the attributes of some people in a queue (not necessarily in order).
Each people[i] = [hi, ki] represents the ith person of height hi
with exactly ki other people in front who have a height greater than or equal to hi.

Reconstruct and return the queue that is represented by the input array people.
The returned queue should be formatted as an array queue,
where queue[j] = [hj, kj] is the attributes of the jth person
in the queue (queue[0] is the person at the front of the queue).

Example 1:

Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
*/












/*
Pick out tallest group of people and sort them in a subarray (S).
Since there's no other groups of people taller than them,
therefore each guy's index will be just as same as his k value.

For 2nd tallest group (and the rest),
insert each one of them into (S) by k value.
So on and so forth.

E.g.
input: [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
subarray after step 1: [[7,0], [7,1]]
subarray after step 2: [[7,0], [6,1], [7,1]]
*/

class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& P) {
		sort(P.begin(), P.end(),[](auto& a, auto& b){
			return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
		});

		vector<vector<int>> ans; ans.reserve(P.size());
		for (auto& p : P)
			ans.insert(ans.begin() + p[1], p);

		return ans;
	}
};
/*
k is only determined by people with equal or larger height,
so makes sense to insert in non-increasing order of height.
Because when we insert some person with height h and count k,
we know that we have found its correct position
relative to people with equal and larger height.

And when we later insert other people with equal or smaller height,
we know that it will not affect this relative position.
So the answer is right after we insert all people.
*/