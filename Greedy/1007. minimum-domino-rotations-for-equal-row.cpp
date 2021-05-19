// https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/






class Solution {
public:
	int minDominoRotations(vector<int>& A, vector<int>& B) {
		int ans = A.size();
		if (isPossible(A, B, A[0]))
			ans = min(ans, getMinFlips(A, B, A[0]));
		if (isPossible(A, B, B[0]))
			ans = min(ans, getMinFlips(A, B, B[0]));
		return ans == A.size() ? -1 : ans;
	}

	bool isPossible(vector<int>& A, vector<int>& B, int cand) {
		for (int i = 0; i < A.size(); i++) {
			if (A[i] != cand and B[i] != cand)
				return false;
		}
		return true;
	}

	int getMinFlips(vector<int>& A, vector<int>& B, int cand) {
		int upper = 0, lower = 0;
		for (int i = 0; i < A.size(); i++) {
			if (A[i] == cand && B[i] == cand)
				continue;
			upper += A[i] == cand;
			lower += B[i] == cand;
		}
		return min(upper, lower);
	}
};



// remove isPossible fn,
// we can verify possibility by checking upper+lower+both = size
class Solution {
public:
	int minDominoRotations(vector<int>& A, vector<int>& B) {
		int ans = A.size();
		ans = min(ans, getMinFlips(A, B, A[0]));
		ans = min(ans, getMinFlips(A, B, B[0]));
		return ans == A.size() ? -1 : ans;
	}

	int getMinFlips(vector<int>& A, vector<int>& B, int cand) {
		int upper = 0, lower = 0, both = 0;
		for (int i = 0; i < A.size(); i++) {
			if (A[i] == cand && B[i] == cand) both++;
			else if (A[i] == cand) upper++;
			else if (B[i] == cand) lower++;
		}
		if (upper + lower + both != A.size()) return A.size();
		return min(upper, lower);
	}
};