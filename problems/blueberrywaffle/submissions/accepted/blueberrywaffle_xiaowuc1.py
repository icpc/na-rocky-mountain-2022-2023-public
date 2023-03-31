#!/usr/bin/python3
r, f = (int(x) for x in input().split())
print("up" if (f // r + ((f % r) * 2 > r))%2==0 else "down")