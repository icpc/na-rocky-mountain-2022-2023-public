#!/usr/bin/python3
n, k = (int(x) for x in input().split())
val = 0
ans = 0

for i in range(1, n+1):
	for j in range(len(str(i))):
		val *= 10
		val %= k
	val += i
	val %= k
	if val == 0:
		ans += 1

print (ans)
