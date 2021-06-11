# https://leetcode.com/problems/median-of-two-sorted-arrays/


'''
Approach 1 - BINARY SEARCH O(log(min(n, m)))

perform BS to find the correct partition in array1,
according to it only, partition in array2 is determined


Approach 2 – Divide & conquer O(log(m+n))

Also, we can use algo of find kth element in 2 sorted arrays.
We divide both arr in 2 parts each.

-If k lies in 1st part of merged sorted arr,
 eliminate second half of any one arraybased on their medians.
-else k lies in second half,
 so eliminate first half of any one array based on their medians.

'''
# approach 2 - D&C

class Solution:
	def findMedianSortedArrays(self, A: List[int], B: List[int]) -> float:
		l = len(A) + len(B)
		if (l % 2 == 1):
			return self.Kth(A, B, l // 2)
		else:
			return (self.Kth(A, B, l // 2) + self.Kth(A, B, l // 2 - 1)) / 2

	

	def Kth(self, A, B, k) -> int:

		if not A: return B[k]
		if not B: return A[k]

		ia, ib = len(A)//2, len(B)//2
		ma, mb = A[ia], B[ib]

		# since k index lies in first half of merged sorted arr,
		# we can eliminate second part of any one arr based on medians
		
		if k <= ia + ib:
			if mb > ma:
				return self.Kth(A, B[:ib], k)
			else:
				return self.Kth(A[:ia], B, k)
		
		# since k index lies in second half of merged sorted arr,
		# we can eliminate first part of any one arr based on medians
		
		elif k > ia + ib:
			if mb > ma:
				return self.Kth(A[ia+1: ], B, k-(ia+1))
			else:
				return self.Kth(A, B[ib+1: ], k-(ib+1))

		# subtracted (ia+1) bcz we remove ia+1 number of elements
		# since ia is index, so # of ele till ia is ia+1

