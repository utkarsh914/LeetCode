# https://leetcode.com/problems/find-eventual-safe-states/

'''
We start at some node in a directed graph, and every turn,
we walk along a directed edge of the graph.
If we reach a terminal node (that is, it has no outgoing directed edges), we stop.

We define a starting node to be safe if we must eventually walk to a terminal node.
More specifically, there is a natural number k,
so that we must have stopped at a terminal node in less than k steps
for any choice of where to walk.

Return an array containing all the safe nodes of the graph.
The answer should be sorted in ascending order.

The directed graph has n nodes with labels from 0 to n - 1,
where n is the length of graph.
The graph is given in the following form:
graph[i] is a list of labels j such that (i, j)
is a directed edge of the graph, going from node i to node j.

'''









'''
Just move along unvisited (-1) nodes and remark them as 0 on the queue
while visiting others on the path and finish them as 1.
If you meet them again on the queue while visiting (being 0)
it means you completed a cycle,
in other words it is not safe and return back without adding.
'''
class Solution:
	def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
		
		def hasCycle(u, vis, recStack):
			vis[u] = True
			recStack.add(u)
			# if v is visited and in the stack, cycle exists
			for v in graph[u]:
				if not vis[v]:
					if hasCycle(v, vis, recStack): return True
				elif v in recStack: return True
			# remove from recursion stack
			recStack.remove(u)
			return False
		

		N = len(graph)
		vis = [False] * N
		recStack = set()
		unsafe = set()
		
		for u in range(N):
			if not vis[u] and hasCycle(u, vis, recStack):
				unsafe.update(recStack)
			
		return sorted([n for n in range(N) if not n in unsafe])






'''
----- do the reverse of above ------

directly add those nodes to answer, which successfully complete the DFS
'''
class Solution:
	def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
		
		def hasCycle(u, vis, recStack):
			vis[u] = True
			recStack.add(u)
			# if v is visited and in the stack, cycle exists
			for v in graph[u]:
				if not vis[v]:
					if hasCycle(v, vis, recStack): return True
				elif v in recStack: return True
			# remove from recursion stack
			recStack.remove(u)
			ans.append(u)
			return False
		

		N = len(graph)
		vis = [False] * N
		recStack = set()
		ans = []
		
		for u in range(N):
			if not vis[u]:
				hasCycle(u, vis, recStack)
			
		return sorted(ans)






'''
------- even shorer than above ------
in vis array:
	-1 -> not visited
	0 -> element is in stack
	1 -> completed successfully

rest same as above
'''
class Solution:
	def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
		
		def hasCycle(u):
			vis[u] = 0
			# if v is visited and in the stack, cycle exists
			for v in graph[u]:
				if vis[v] == 0 or (vis[v] == -1 and hasCycle(v)):
					return True
			# remove from recursion stack
			vis[u] = 1
			ans.append(u)
			return False
		

		N = len(graph)
		vis = [-1] * N
		ans = []
		
		for u in range(N):
			if vis[u] == -1: hasCycle(u)
			
		return sorted(ans)






def eventualSafeNodes(self, g: List[List[int]]) -> List[int]:
	seen, safe = set(), set()
	def dfs(u, path):
		if u in seen: return u in safe
		seen.add(u)
		if all(dfs(v, path|{v}) for v in g[u]): safe.add(u); return True
	return list(filter(lambda u: dfs(u, {u}), range(len(g))))