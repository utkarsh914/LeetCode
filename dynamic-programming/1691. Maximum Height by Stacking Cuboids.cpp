// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/

/*
Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.

You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj. You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.

Return the maximum height of the stacked cuboids.

 

Example 1:



Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
Output: 190
Explanation:
Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
Cuboid 0 is placed next with the 45x20 side facing down with height 50.
Cuboid 2 is placed next with the 23x12 side facing down with height 45.
The total height is 95 + 50 + 45 = 190.
Example 2:

Input: cuboids = [[38,25,45],[76,35,3]]
Output: 76
Explanation:
You can't place any of the cuboids on the other.
We choose cuboid 1 and rotate it so that the 35x3 side is facing down and its height is 76.
Example 3:

Input: cuboids = [[7,11,17],[7,17,11],[11,7,17],[11,17,7],[17,7,11],[17,11,7]]
Output: 102
Explanation:
After rearranging the cuboids, you can see that all cuboids have the same dimension.
You can place the 11x7 side down on all cuboids so their heights are 17.
The maximum height of stacked cuboids is 6 * 17 = 102.
 

Constraints:

n == cuboids.length
1 <= n <= 100
1 <= widthi, lengthi, heighti <= 100
*/










/*
same as "LONGEST INCREASING SUBSEQUENCE"

Intuition

There is something midleading here, you need to understand the differnece.
If the question is:
"You can place cuboid i on cuboid j if width[i] <= width[j] and length[i] <= length[j]"
that's will be difficult.

But it's
"You can place cuboid i on cuboid j if width[i] <= width[j] and length[i] <= length[j] and height[i] <= height[j]"
That's much easier.


Explanation
You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.
So for each cuboid, we sort its length in three dimension.

You can place cuboid i on cuboid j,
we have
width[i] <= width[j] and length[i] <= length[j] and height[i] <= height[j].

This condition will hold, after we sort each cuboid length,
that is,
small[i] <= small[j] and mid[i] <= mid[j] and big[i] <= big[j].

We apply a brute for doulbe for loop,
to compare each pair of cuboids,
check if they satifify the condition samll[i] <= small[j] and mid[i] <= mid[j] and big[i] <= big[j]
If so, we can place cuboid i on cuboid j.

You may concern whether area[i] <= area[j].
Don't worry, we always put the big[i] as the height,
the area (width,length) = (small[i], mid[j]),
and we have checked samll[i] <= small[j] && mid[i] <= mid[j].
*/
	int maxHeight(vector<vector<int>>& A) {
		for (auto& a : A)
			sort(begin(a), end(a));

		A.push_back({0, 0, 0});
		sort(begin(A), end(A));

		int n = A.size(), res = 0;
		vector<int> dp(n);

		for (int j = 1; j < n; ++j) {
			for (int i = 0; i < j; ++i) {
				if (A[i][0] <= A[j][0] and A[i][1] <= A[j][1] and A[i][2] <= A[j][2]) {
					dp[j] = max(dp[j], dp[i] + A[j][2]);
					res = max(res, dp[j]);
				}
			}
		}

		return res;
	}








/*
follow up: what if height[i] <= height[j] is not the requirement

in this case, we'll need to try all combinations.
pick every length as height, and check for previous
*/
class Solution {
public:
	int maxHeight(vector<vector<int>>& cuboids) {
		for (auto& c : cuboids)
			sort(begin(c), end(c));
		// sort by volume
		sort(cuboids.begin(), cuboids.end(), [](auto& a, auto& b) {
			return a[0]*a[1]*a[2] < b[0]*b[1]*b[2];
		});
		
		int n = cuboids.size();
		int dp[n][3];
		int ans = 0;
		
		for (int i = 0; i < n; i++) {
			auto& cur = cuboids[i];
			dp[i][0] = cur[0];
			dp[i][1] = cur[1];
			dp[i][2] = cur[2];
			
			for (int j = 0; j < i; j++) {
				auto& prev = cuboids[j];

				// take every index as height
				for (int k = 0; k < 3; k++) {
					// idx keeps indices that are not taken (i.e. indices except k)
					vector<int> idx {0,1,2}; idx.erase(idx.begin() + k);
					int cur_h = cur[k];
					int cur_l = max(cur[idx[0]], cur[idx[1]]);
					int cur_w = min(cur[idx[0]], cur[idx[1]]);
					
					for (int l = 0; l < 3; l++) {
						// idx keeps indices that are not taken (i.e. indices except l)
						vector<int> idx {0,1,2}; idx.erase(idx.begin() + l);
						int prev_h = prev[l];
						int prev_l = max(prev[idx[0]], prev[idx[1]]);
						int prev_w = min(prev[idx[0]], prev[idx[1]]);
						
						if (cur_h >= prev_h and cur_l >= prev_l and cur_w >= prev_w)
							dp[i][k] = max(dp[i][k], dp[j][l] + cur_h);
					}

				}

			}
			
			ans = max({ ans, dp[i][0], dp[i][1], dp[i][2] });
		}
		
		return ans;
	}
};