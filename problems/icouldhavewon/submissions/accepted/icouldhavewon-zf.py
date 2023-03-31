#!/bin/python3

matches = input()

vals = []
for k in range(1, len(matches)+1):
    aset = bset = a = b = 0
    for x in matches:
        if x == "A": a += 1
        else: b += 1
        if max(a, b) == k:
            if a == k: aset += 1
            else: bset += 1
            a = b = 0
    if aset > bset: vals.append(k)

print(len(vals))
print(*vals)
