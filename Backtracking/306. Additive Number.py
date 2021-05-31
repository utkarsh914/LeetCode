# https://leetcode.com/problems/additive-number/submissions/

class Solution:
	def isAdditiveNumber(self, s) -> bool:

		def backtrack(s, start) -> bool:	
			if start == len(s) and len(self.cur) >= 3: return True
			
			for i in range(start, len(s)):
				if s[start] == '0' and i > start: break
				N = int(s[start : i+1])
				l = len(self.cur)
				if l <= 1 or self.cur[l-1] + self.cur[l-2] == N:
					self.cur.append(N)
					if (backtrack(s, i+1)):
						return True
					self.cur.pop()

			return False

		self.cur = []
		return backtrack(s, 0)