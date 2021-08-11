// https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/

/*
There are n projects numbered from 0 to n - 1. You are given an integer array milestones where each milestones[i] denotes the number of milestones the ith project has.

You can work on the projects following these two rules:

Every week, you will finish exactly one milestone of one project. You must work every week.
You cannot work on two milestones from the same project for two consecutive weeks.
Once all the milestones of all the projects are finished, or if the only milestones that you can work on will cause you to violate the above rules, you will stop working. Note that you may not be able to finish every project's milestones due to these constraints.

Return the maximum number of weeks you would be able to work on the projects without violating the rules mentioned above.

 

Example 1:

Input: milestones = [1,2,3]
Output: 6
Explanation: One possible scenario is:
​​​​- During the 1st week, you will work on a milestone of project 0.
- During the 2nd week, you will work on a milestone of project 2.
- During the 3rd week, you will work on a milestone of project 1.
- During the 4th week, you will work on a milestone of project 2.
- During the 5th week, you will work on a milestone of project 1.
- During the 6th week, you will work on a milestone of project 2.
The total number of weeks is 6.
Example 2:

Input: milestones = [5,2,1]
Output: 7
Explanation: One possible scenario is:
- During the 1st week, you will work on a milestone of project 0.
- During the 2nd week, you will work on a milestone of project 1.
- During the 3rd week, you will work on a milestone of project 0.
- During the 4th week, you will work on a milestone of project 1.
- During the 5th week, you will work on a milestone of project 0.
- During the 6th week, you will work on a milestone of project 2.
- During the 7th week, you will work on a milestone of project 0.
The total number of weeks is 7.
Note that you cannot work on the last milestone of project 0 on 8th week because it would violate the rules.
Thus, one milestone in project 0 will remain unfinished.
 

Constraints:

n == milestones.length
1 <= n <= 105
1 <= milestones[i] <= 109
*/






/*
similar:

https://leetcode.com/problems/task-scheduler/
https://leetcode.com/problems/maximum-score-from-removing-stones/
https://leetcode.com/problems/reorganize-string/

https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/
https://leetcode.com/problems/painting-a-grid-with-three-different-colors/

*/




class Solution {
public:
	long long numberOfWeeks(vector<int>& A) {
		long sum = accumulate(A.begin(), A.end(), 0L);
		long mx = *max_element(A.begin(), A.end());
		long rest = sum - mx;
		if (rest >= mx) return sum;
		else return 1 + 2L * rest;
	}
};
/*
1. If there are at least two occurence of the maximum milestones value,
	we can finish all milestones.

	Example
	Let's say we have milestones like [5, 5, 3, 2].
	We can take turn working on those projects with the most milestones.
	So, [5, 5] will become [4, 4], then become [3, 3].
	Because we have another project with 3 milestones, so we can take turn working on [3, 3, 3].
	[3, 3, 3] after three rounds, will become [2, 2, 2].
	[2, 2, 2, 2] -> [1, 1, 1, 1] -> [0, 0, 0, 0] -> all the milestones are finished.
	

2. If not so, we will try to group rest milestones to become equal to max.
	If we can do this, it becomes same as case 1.

	Here's a example with the max milestone don't get its pair:
	Q: [5,7,5,7,7,9], to make it easier to explain, Ill sort it but it's unnecessary

	[9,(7,7),7,5,5] -> form "one" new milestones that match the major one with (7,7), to (9,5) -> [9,9,7,5,5,5]
	[9,9,7,5,5,5] -> [7,7,7,5,5,5] , ans += 2 (9 to 7) *2(components) ,ans =4
	[7,7,7,5,5,5] -> [5,5,5,5,5,5], ans += 2 (7 to 5) * 3 (comps), ans = 10
	[5,5,5,5,5,5] -> [0,0,0,0,0,0], ans += 5 (5 to 0) * 6 (comps), ans = 40
	So, if we can form "at least one" new project, the whole list should be finished,
	and whether we can form it or not can simply be done by "_sum >= _max".
	This is for the first part of the code.
	Next, the second part:

	dealing with the scenarios that we can't even form one new project with the rest of them.
	So what we do is to fill the most milestones as much as we can.
	Q: [5,2,1]

	the rest = 3, smaller than max = 5, which means it will left 2 milestones undone
	for the max one. (2 * rest part)
	But we can start our work with the max one, so + 1 with the ans (+1 part)




***** Incorrect strategy ****
	If you try to work on the top milestones and until one is all finished.
	Can consider the test case [100, 100, 100].
	(Answer should be 300, but many will get 201 if using the wrong strategy)
*/