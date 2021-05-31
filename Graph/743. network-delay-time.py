# https://leetcode.com/problems/network-delay-time/


class Solution:
	def networkDelayTime(self, times: List[List[int]], n: int, source: int) -> int:
		# build graph
		graph = [[] for _ in range(n)]
		for u, v, w in times:
			graph[u-1].append((v-1, w))

		# return self.bellman_ford(graph, n, source-1)
		# return self.dijkstra_ALgo(graph, n, source-1)
		return self.dijkstra_with_heap(graph, n, source-1)



	# -------------- BELLMAN FORD ----------------
	def bellman_ford(self, graph, n, source) -> int:
		dist = [float("inf")] * n
		dist[source] = 0
		# to update min distance {a path can have at most N-1 edges}
		for _ in range(n-1):
			# explore all edges
			for u in range(n):
				for v, w in graph[u]:
					if dist[u]!=float("inf") and dist[u] + w < dist[v]:
						dist[v] = dist[u] + w

		ans = max(dist)
		return ans if ans < float("inf") else -1



	# -------------- DIJKSTRA ----------------
	def dijkstra_ALgo(self, graph, n, source) -> int:
		finalized = [False] * n
		dist = [float("inf")] * n
		dist[source] = 0

		# returns min dist vertex (from source) that isn't yet finalized
		def getMinDistVertex():
			index, minDist = -1, float("inf");
			for i, d in enumerate(dist):
				if not finalized[i] and d < minDist:
					index, minDist = i, d
			return index
			# return dist.index(min([d for i, d in enumerate(dist) if not finalized[i]]))

		for _ in range(n - 1):
			# pick min dist vertex that isn't yet finalized
			u = getMinDistVertex()
			finalized[u] = True

			for v, w in graph[u]:
				if not finalized[v]:
					dist[v] = min(dist[v], dist[u] + w)

		ans = max(dist)
		return ans if ans < float("inf") else -1



	# -------------- DIJKSTRA with min Heap ----------------
	def dijkstra_with_heap(self, graph, n, source) -> int:
		dist = [float("inf")] * n
		heap = [(0, source)]

		while heap:
			d, u = heapq.heappop(heap)
			if d < dist[u]:
				dist[u] = d
				for v, w in graph[u]:
					heapq.heappush(heap, (d+w, v))

		ans = max(dist)
		return ans if ans < float("inf") else -1


















import heapq
from collections import deque
from collections import defaultdict

# """
#  Uses simple DFS - Accepted
class Solution(object):
	def networkDelayTime(self, times, N, K):
		graph = defaultdict(list)
		for u, v, w in times:
			graph[u].append((v, w))
		distance = {node: float("inf") for node in range(1, N + 1)}
		self.DFS(graph, distance, K, 0)
		totalTime = max(distance.values())
		return totalTime if totalTime < float("inf") else -1

	def DFS(self, graph, distance, node, elapsedTimeSoFar):
		if elapsedTimeSoFar >= distance[node]:   # signal aalreaady reached to this node. so no need to explore for this node
			return
		distance[node] = elapsedTimeSoFar
		for neighbour, time in sorted(graph[node]):
			self.DFS(graph, distance, neighbour, elapsedTimeSoFar + time)
# """


# """
#  Uses simple BFS - Accepted
class Solution:
	def networkDelayTime(self, times, N, K):
		elapsedTime, graph, queue = [0] + [float("inf")] * N, defaultdict(list), deque([(0, K)])
		for u, v, w in times:
			graph[u].append((v, w))
		while queue:
			time, node = queue.popleft()
			if time < elapsedTime[node]:
				elapsedTime[node] = time
				for v, w in graph[node]:
					queue.append((time + w, v))
		mx = max(elapsedTime)
		return mx if mx < float("inf") else -1
# """



# """
# Dijkstra algorithm - Accepted
class Solution:
	def networkDelayTime(self, times, N, K):
		elapsedTime, graph, heap = [0] + [float("inf")] * N, defaultdict(list), [(0, K)]
		for u, v, w in times:
			graph[u].append((v, w))
		while heap:
			time, node = heapq.heappop()
			if time < elapsedTime[node]:
				elapsedTime[node] = time
				for v, w in graph[node]:
					heapq.heappush(heap, (time + w, v))
		mx = max(elapsedTime)
		return mx if mx < float("inf") else -1
# """



# """
# Original Bellman–Ford algorithm - Accepted
class Solution:
	def networkDelayTime(self, times, N, K):
		distance = [float("inf") for _ in range(N)]
		distance[K-1] = 0
		for _ in range(N-1):
			for u, v, w in times:
				if distance[u-1] + w < distance[v-1]:
					distance[v-1] = distance[u-1] + w
		return max(distance) if max(distance) < float("inf") else -1
# """



# """
# Shortest Path Faster Algorithm (SPFA): An improvement of the Bellman–Ford algorithm - Accepted
class Solution:
	def networkDelayTime(self, times, N, K):
		elapsedTime, graph, queue = [0] + [float("inf")] * N, defaultdict(list), deque([(0, K)])
		elapsedTime[K] = 0
		for u, v, w in times:
			graph[u].append((v, w))
		while queue:
			time, node = queue.popleft()
			for neighbour in graph[node]:
				v, w = neighbour
				if time + w < elapsedTime[v]:
					elapsedTime[v] = time + w
					queue.append((time + w, v))
		mx = max(elapsedTime)
		return mx if mx < float("inf") else -1
# """





# """
#  Floyd Warshall - Accepted
class Solution:
	def networkDelayTime(self, times, N, K):
		elapsedTimeMatrix = [[float("inf") for _ in range(N)] for _ in range(N)]
		for u, v, w in times:
			elapsedTimeMatrix[u - 1][v - 1] = w
		for i in range(N):					  #   Assigning 0 to the diagonal cells
			elapsedTimeMatrix[i][i] = 0
		for k in range(N):
			for i in range(N):
				for j in range(N):
					elapsedTimeMatrix[i][j] = min(elapsedTimeMatrix[i][j], elapsedTimeMatrix[i][k] + elapsedTimeMatrix[k][j])
		mx = max(elapsedTimeMatrix[K - 1])
		return mx if mx < float("inf") else -1
# """