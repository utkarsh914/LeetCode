// https://leetcode.com/problems/bulb-switcher-iii/

/*
There is a room with n bulbs, numbered from 1 to n, arranged in a row from left to right.
Initially, all the bulbs are turned off.

At moment k (for k from 0 to n - 1), we turn on the light[k] bulb.
A bulb change color to blue only if it is on and all the previous bulbs
(to the left) are turned on too.

Return the number of moments in which all turned on bulbs are blue.
*/



/*
same as - 769. https://leetcode.com/problems/max-chunks-to-make-sorted/
*/
class Solution {
public:
	int numTimesAllBlue(vector<int>& light) {
		vector<int> sorted = light;
		sort(sorted.begin(), sorted.end());
		
		int s1 = 0, s2 = 0, ans = 0;
		for (int i=0; i < light.size(); i++) {
			s1 += light[i];
			s2 += sorted[i];
			if (s1 == s2) ans++;
		}
		return ans;
	}
};