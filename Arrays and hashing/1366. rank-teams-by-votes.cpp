// https://leetcode.com/problems/rank-teams-by-votes/

/*
In a special ranking system, each voter gives a rank from highest to lowest
to all teams participated in the competition.

The ordering of teams is decided by who received the most position-one votes.
If two or more teams tie in the first position, we consider the second position to resolve the conflict,
if they tie again, we continue this process until the ties are resolved.
If two or more teams are still tied after considering all positions,
we rank them alphabetically based on their team letter.

Given an array of strings votes which is the votes of all voters in the ranking systems.
Sort all teams according to the ranking system described above.

Return a string of all teams sorted by the ranking system.

 

Example 1:

Input: votes = ["ABC","ACB","ABC","ACB","ACB"]
Output: "ACB"
Explanation: Team A was ranked first place by 5 voters.
No other team was voted as first placeso team A is the first team.
Team B was ranked second by 2 voters and was ranked third by 3 voters.
Team C was ranked second by 3 voters and was ranked third by 2 voters.
As most of the voters ranked C second, team C is the second team and team B is the third.
*/


/*
Build array rank where rank[i][j] is the number of votes for team i to be the j-th rank.
Sort the trams by rank array. if rank array is the same for two or more teams, sort them by the ID in ascending order.
*/
class Solution {
public:
	string rankTeams(vector<string>& votes) {
		vector<vector<int>> count(26, vector<int>(26, 0));
		for (auto& vote : votes) {
			for (int i=0; i < vote.length(); i++)
				count[vote[i]-'A'][i]++;
		}

		string ans = votes[0];
		sort(ans.begin(), ans.end(), [&count](char& c1, char& c2) {
			for (int i=0; i<26; i++) {
				if (count[c1-'A'][i] != count[c2-'A'][i])
					return count[c1-'A'][i] > count[c2-'A'][i];
			}
			// There is a tie and we rank teams ascending by their IDs.
			return c1 < c2;
		});
		
		return ans;
	}
};