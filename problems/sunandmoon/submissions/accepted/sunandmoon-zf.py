#!/bin/python3

d1, y1 = map(int, input().split())
d2, y2 = map(int, input().split())

tot = 0
while not tot or d1%y1 or d2%y2:
    tot, d1, d2 = tot+1, d1+1, d2+1

print(tot)
