#!/usr/bin/env python3 

cur = []
periods = []
for _ in range(2):
    d, y = map(int, input().split())
    cur.append(d)
    periods.append(y)

ans = 0
while ans == 0 or cur != [0, 0]:
    ans += 1
    cur = [(x + 1) % y for x, y in zip(cur, periods)]

print(ans)
