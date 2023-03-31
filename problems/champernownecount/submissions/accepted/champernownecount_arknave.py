#!/usr/bin/env python3

n, k = map(int, input().split())
cur = 0
ans = 0

shift = 10
for d in range(1, n + 1):
    if d == shift:
        shift *= 10

    cur = (cur * shift + d) % k
    ans += cur == 0

print(ans)
