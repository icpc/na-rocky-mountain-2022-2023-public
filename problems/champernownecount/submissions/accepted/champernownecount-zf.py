#!/bin/python3

n, k = map(int, input().split())

tot = cur = 0

for a in range(1, n+1):
    cur = (cur*(10**len(str(a))) + a)%k
    if cur == 0: tot += 1
print(tot)
