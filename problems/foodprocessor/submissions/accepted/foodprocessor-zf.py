#!/bin/python3

import heapq, math

s, t, n = map(int, input().split())

blades = sorted([tuple(map(int, input().split())) for _ in range(n)])[::-1]

if blades[0][0] < s:
    print(-1)
elif s == t:
    print(0)
else:
    sec = 0.0
    cur_h = blades[0][1]
    for m, h in blades:
        n_size = max(t, min(m, s))
        sec += cur_h * math.log2(s / n_size)
        cur_h = min(h, cur_h)
        s = n_size
    sec += cur_h * math.log2(s/t)
    print(sec)
