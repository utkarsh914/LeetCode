// https://leetcode.com/problems/closest-room/

/*
There is a hotel with n rooms. The rooms are represented by a 2D integer array rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.

You are also given k queries in a 2D array queries where queries[j] = [preferredj, minSizej]. The answer to the jth query is the room number id of a room such that:

The room has a size of at least minSizej, and
abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
If there is a tie in the absolute difference, then use the room with the smallest such id. If there is no such room, the answer is -1.

Return an array answer of length k where answer[j] contains the answer to the jth query.

 

Example 1:

Input: rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
Output: [3,-1,3]
Explanation: The answers to the queries are as follows:
Query = [3,1]: Room number 3 is the closest as abs(3 - 3) = 0, and its size of 2 is at least 1. The answer is 3.
Query = [3,3]: There are no rooms with a size of at least 3, so the answer is -1.
Query = [5,2]: Room number 3 is the closest as abs(3 - 5) = 2, and its size of 2 is at least 2. The answer is 3.
Example 2:

Input: rooms = [[1,4],[2,3],[3,5],[4,1],[5,2]], queries = [[2,3],[2,4],[2,5]]
Output: [2,1,3]
Explanation: The answers to the queries are as follows:
Query = [2,3]: Room number 2 is the closest as abs(2 - 2) = 0, and its size of 3 is at least 3. The answer is 2.
Query = [2,4]: Room numbers 1 and 3 both have sizes of at least 4. The answer is 1 since it is smaller.
Query = [2,5]: Room number 3 is the only room with a size of at least 5. The answer is 3.
 

Constraints:

n == rooms.length
1 <= n <= 105
k == queries.length
1 <= k <= 104
1 <= roomIdi, preferredj <= 107
1 <= sizei, minSizej <= 107
*/











/*
 ===== Idea ====
Because we need the room which has minSize by the given query,
so we can iterate from the largest minSize query
and put all the valid room to an ordered set,
and then do binary search to get room id in the ordered set.

Complexity:
Time - O(max(nLog(n), mLog(m))) n is rooms length, m is queries length.
Space - O(n)
*/
class Solution {
public:
	vector<int> closestRoom(vector<vector<int>>& R, vector<vector<int>>& Q) {
		// sort rooms by size in desc, on tie, by room id
		auto comp = [](auto& a, auto& b) {
			return a[1] > b[1];
		};
		sort(R.begin(), R.end(), comp);
		
		// sort queries by size in dec
		// also store orig indices of queries in themselves only
		for (int i = 0; i < Q.size(); i++) {
			Q[i].push_back(i);
		}
		sort(Q.begin(), Q.end(), comp);

		set<int> set;
		vector<int> ans(Q.size());
		int i = 0;

		for (auto& q : Q) {
			int preferID = q[0], minsize = q[1], index = q[2];

			while (i < R.size() and R[i][1] >= minsize) {
				set.insert(R[i][0]), i++;
			}

			if (set.size() > 0) {
				auto itr = set.upper_bound(preferID);
				int diff = INT_MAX, ansRoomID = INT_MAX;
				if (itr != set.end()) {
					diff = abs(*itr - preferID);
					ansRoomID = *itr;
				}
				if (itr != set.begin()) {
					--itr;
					if (abs(*itr - preferID) <= diff) {
						diff = abs(*itr - preferID);
						ansRoomID = *itr;
					}
				}
				ans[index] = ansRoomID;
			}
			else {
				ans[index] = -1;
			}
		}

		return ans;
	}
};