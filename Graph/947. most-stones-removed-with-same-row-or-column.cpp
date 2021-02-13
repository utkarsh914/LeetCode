/*
https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.
A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone,
return the largest possible number of stones that can be removed.

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
*/

/*
Problem:
we can remove a stone if and only if,
there is another stone in the same column OR row.
We try to remove as many as stones as possible.

One sentence to solve:
Connected stones can be reduced to 1 stone,
the maximum stones can be removed = stones number - islands number.
so just count the number of "islands".
*/
class Solution {
public:

int islands = 0;
unordered_map<int, int> mp;

int find(int x) {
	if (!mp.count(x)) {
		mp[x] = x;
		islands++;
		return x;
	}
	if (mp[x] != x)	mp[x] = find(mp[x]);
	return mp[x];
}

void uni(int x, int y) {
	x=find(x), y=find(y);
	if (x != y) mp[y]=x, islands--;
}

int removeStones(vector<vector<int>>& stones) {
	for (auto& s:stones) {
		uni(s[0], 10001+s[1]);
	}
	return stones.size() - islands;
}};





// ************** DFS IN JAVA ****************
class Solution {
	public int removeStones(int[][] stones) {
		if(stones == null) {
			return 0;
		}
	
		int islandsCount = 0;
		Set<String> visited = new HashSet();
		for(int i=0; i<stones.length; i++) {
			if(!visited.contains(stones[i][0]+"-"+stones[i][1])) {
				islandsCount++;
				helper(stones, stones[i][0], stones[i][1], visited);
			} 
		}
		return stones.length-islandsCount;
	}

	private void helper(int[][] stones, int row, int col, Set<String> visited){
		visited.add(row+"-"+col);
		for(int[] stone : stones) {
			if((stone[0]==row || stone[1]==col) && !visited.contains(stone[0]+"-"+stone[1])){
				helper(stones, stone[0], stone[1], visited);
			}
		}
	}
}