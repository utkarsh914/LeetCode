// https://leetcode.com/problems/get-watched-videos-by-your-friends/

/*
There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.

Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest. 

 

Example 1:



Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
Output: ["B","C"] 
Explanation: 
You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
Person with id = 1 -> watchedVideos = ["C"] 
Person with id = 2 -> watchedVideos = ["B","C"] 
The frequencies of watchedVideos by your friends are: 
B -> 1 
C -> 2
Example 2:



Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
Explanation: 
You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
 

Constraints:

n == watchedVideos.length == friends.length
2 <= n <= 100
1 <= watchedVideos[i].length <= 100
1 <= watchedVideos[i][j].length <= 8
0 <= friends[i].length < n
0 <= friends[i][j] < n
0 <= id < n
1 <= level < n
if friends[i] contains j, then friends[j] contains i
Accepted
*/





/*
first run BFS from id and gather all the friends that are at a distance of K
into an array neededFriends.
then take all the vids that are watched by those friends,
store their freq count in a map. then sort those videos by freq,
and return the sorted array
*/
class Solution {
public:
	vector<string> watchedVideosByFriends(
		vector<vector<string>>& vid,
		vector<vector<int>>& friends, int id, int level) {

		vector<bool> taken(101, false);
		vector<int> neededFriends;
		queue<int> q;
		q.push(id);
		taken[id] = true;

		while (!q.empty()) {
			if (level < 0) break;
			int size = q.size();
			while (size--) {
				int cur = q.front(); q.pop();
				if (level == 0) {
					neededFriends.push_back(cur);
				}
				for (int& f : friends[cur]) {
					if (taken[f] == false)
						q.push(f), taken[f] = true;
				}
			}
			level--;
		}

		unordered_map<string, int> map;
		for (int& f : neededFriends)
			for (string& v : vid[f])
				map[v]++;

		vector<pair<string, int>> vec(map.begin(), map.end());

		// sort the vector by freq, tie break by alphabetical
		sort(vec.begin(), vec.end(), [](auto& p1, auto& p2) {
			if (p1.second == p2.second) return p1.first < p2.first;
			return p1.second < p2.second;
		});

		vector<string> ans;
		for (auto& p : vec) ans.push_back(p.first);

		return ans;
	}
};