// https://leetcode.com/problems/single-number/

/*
we have to know the bitwise XOR
0 ^ N = N
N ^ N = 0
So..... if N is the single number

N1 ^ N1 ^ N2 ^ N2 ^..............^ Nx ^ Nx ^ N
= (N1^N1) ^ (N2^N2) ^..............^ (Nx^Nx) ^ N
= 0 ^ 0 ^ ..........^ 0 ^ N
= N
*/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int ans = 0;
		for (int n:nums) ans ^= n;
		return ans;
	}
};