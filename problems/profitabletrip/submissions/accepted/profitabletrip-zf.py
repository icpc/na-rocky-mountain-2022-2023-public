#!/bin/python3

n, m, w = map(int, input().split())

g = [[] for _ in range(n+1)]

for _ in range(m):
  u, v, p = map(int, input().split())
  g[u].append((v,p))

INF = 10**9
best = [-INF for _ in range(n+1)]
best[1] = 0
todo = [1]

while todo:
  u = todo.pop()

  for v,p in g[u]:
    nc = min(w, best[u]+p)
    if nc > best[v]:
      best[v] = nc
      todo.append(v)

print(best[n])
