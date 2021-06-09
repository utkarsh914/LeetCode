// https://leetcode.com/problems/decode-xored-permutation/

/*
There is an integer array perm that is a permutation of the first n positive integers,
where n is always odd.

It was encoded into another integer array encoded of length n - 1,
such that encoded[i] = perm[i] XOR perm[i + 1].
For example, if perm = [1,3,2], then encoded = [2,1].

Given the encoded array, return the original array perm.
It is guaranteed that the answer exists and is unique.


Example 1:

Input: encoded = [3,1]
Output: [1,2,3]
Explanation: If perm = [1,2,3], then encoded = [1 XOR 2,2 XOR 3] = [3,1]
Example 2:

Input: encoded = [6,5,4,6]
Output: [2,4,1,5,3]
*/









/*
Compute the XOR of the numbers between 1 and n, and think about how it can be used. Let it be x.
Think why n is odd.
perm[0] = x XOR encoded[1] XOR encoded[3] XOR encoded[5] ...
perm[i] = perm[i-1] XOR encoded[i-1]
*/
class Solution {
public:
	vector<int> decode(vector<int>& encoded) {
		int N = encoded.size()+1, xor_upto_n = 0;
		for (int i = 1; i <= N; i++) {
			xor_upto_n = xor_upto_n ^ i;
		}

		vector<int> perm(N);
		perm[0] = xor_upto_n;
		for (int i = 1; i < encoded.size(); i += 2) {
			perm[0] = perm[0] ^ encoded[i];
		}

		for (int i = 1; i < perm.size(); i++) {
			perm[i] = perm[i-1] ^ encoded[i-1];
		}
		
		return perm;
	}
};
/*
Actually since n is odd, we can get the 1 ^ 2 ^ 3 ^ ... ^ n in O(1) time.

Since 2 ^ 3 = 1, 4 ^ 5 = 1, 6 ^ 7 = 1 ...,
so XOR(1) = 1, XOR(3) = 0, XOR(5) = 1, XOR(7) = 0 ... where XOR(n) = 1 ^ 2 ^ ... ^ n.

So XOR(n) = 1 - n / 2 % 2.
*/









/*
when required output doesn't needt to be in range [1,n]
*/
class Solution {
public:
	vector<int> decode(vector<int>& A) {
		vector<int> preXOR = A;
		for (int i = 1; i < preXOR.size(); i++) {
			preXOR[i] = preXOR[i] ^ preXOR[i-1];
		}

		vector<int> ans(A.size() + 1);
		int sum = accumulate(A.begin(), A.end(), 0);
		ans[0] = accumulate(preXOR.begin(), preXOR.end(), 0) ^ sum;

		for (int i = 1; i < ans.size(); i++) {
			ans[i] = ans[i-1] ^ A[i-1];
		}
		
		return ans;
	}
};