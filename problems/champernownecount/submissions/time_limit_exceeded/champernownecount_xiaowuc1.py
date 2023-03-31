#!/usr/bin/python3
n, k = (int(x) for x in input().split())
curr = 0
ret = 0
for i in range(1, n+1):
  curr *= (10 ** len(str(i)))
  curr += i
  ret += curr % k == 0
print(ret)
