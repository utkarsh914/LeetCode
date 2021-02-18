// https://leetcode.com/problems/reverse-bits/

class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t x = 0;
		for (int i = 0; i < 32; i++) {
			uint32_t curBit = (n & (1 << i)) >> i;
			if (curBit) x |= (1 << (31-i));
		}
		return x;
	}
};