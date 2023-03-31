#!/bin/python3

n = int(input())

seqs = []
tops = []

for x in map(int, input().split()):
    # invariant: tops[lo] >= x and tops[hi] < x
    lo, hi = -1, len(tops)
    while lo+1 < hi:
        mid = (lo+hi)//2
        if tops[mid] >= x: lo = mid
        else: hi = mid
    if hi >= len(tops):
        seqs.append([x])
        tops.append(x)
    else:
        seqs[hi].append(x)
        tops[hi] = x

print(len(seqs))
for x in seqs:
    print(*x)
