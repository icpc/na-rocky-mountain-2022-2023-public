#!/bin/python3

import itertools

states = []
for k in range(4): states += itertools.permutations((0,1,2), k)

memo = {s:0 for s in states}

n = int(input())
tasks = []
for _ in range(n):
    tasks.append(int(input()))
for x in tasks[::-1]:
    nxt = {s:0 for s in states}
    for tools in states:
        if not tools: nxt[tools] = memo[tools]
        elif x == tools[-1]: nxt[tools] = 1 + memo[tools]
        else: nxt[tools] = max(nxt[tools[:-1]], memo[tools])
    memo = nxt

print(max(memo.values()))
