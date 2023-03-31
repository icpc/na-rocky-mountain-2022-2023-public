#!/usr/bin/env python3

import math

def rate(start, end, h):
    return h * (math.log2(start) - math.log2(end))

def main():
    s, t, n = map(int, input().split())
    blades = []
    for _ in range(n):
        m, h = map(int, input().split())
        blades.append((m, -h))

    blades.sort()

    filtered_blades = []
    for m, h in blades:
        h = -h
        while filtered_blades and h < filtered_blades[-1][1]:
            filtered_blades.pop()
        
        filtered_blades.append((m, h))

    blades = filtered_blades

    if blades[-1][0] < s:
        print(-1)
        return

    ans = 0.0
    cur = float(s)
    while cur > t:
        m, h = blades.pop()
        goal = blades[-1][0] if blades else t
        goal = max(goal, t)
        goal = min(goal, s)
        r = rate(cur, goal, h)

        ans += r
        cur = goal

    print(ans)


if __name__ == '__main__':
    main()
