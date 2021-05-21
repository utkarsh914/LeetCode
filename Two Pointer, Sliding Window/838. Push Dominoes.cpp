// https://leetcode.com/problems/push-dominoes/

/*
There are N dominoes in a line, and we place each domino vertically upright.

In the beginning, we simultaneously push some of the dominoes either to the left or to the right.


After each second, each domino that is falling to the left pushes the adjacent domino on the left.

Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.

When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.

For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.

Given a string "S" representing the initial state. S[i] = 'L', if the i-th domino has been pushed to the left; S[i] = 'R', if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.

Return a string representing the final state. 

Example 1:

Input: ".L.R...LR..L.."
Output: "LL.RR.LLRRLL.."
Example 2:

Input: "RR.L"
Output: "RR.L"
Explanation: The first domino expends no additional force on the second domino.
*/













/*
First pass, from left to right, only count distance of current index to previous 'R'. Save all distance in dist array
Second pass, from right to left, count distance of current index to previous 'L'. If lDist < rDist (dist[i]), current cell should be 'L', if lDist == rDist, current cell should be '.'
*/

class Solution {
public:
	string pushDominoes(string& D) {
		
		vector<int> LDist(D.size(), INT_MAX);
		vector<int> RDist(D.size(), INT_MAX);

		// nearest 'L' on the right
		bool found = false;
		for (int i = D.size()-1, ind = -1; i >= 0; i--) {
			if (D[i] == 'L') ind = i, found = true;
			else if (D[i] == 'R') found = false; // very important
			if (found) LDist[i] = ind - i;
		}
		// nearest 'R' on the left
		found = false;
		for (int i = 0, ind = -1; i < D.size(); i++) {
			if (D[i] == 'R') ind = i, found = true;
			else if (D[i] == 'L') found = false; // very important
			if (found) RDist[i] = i - ind;
		}

		for (int i = 0; i < D.size(); ++i) {
			if (LDist[i] < RDist[i]) D[i] = 'L';
			else if (LDist[i] > RDist[i]) D[i] = 'R';
			// else if (LDist[i] == RDist[i]) D[i] = '.';
		}

		return D;
	}
};