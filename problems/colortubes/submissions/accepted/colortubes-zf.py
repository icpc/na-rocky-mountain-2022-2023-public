#!/usr/bin/python3

# An O(n^2) solution.

def move(i, j):
    output.append((i+1, j+1))
    tubes[j].append(tubes[i].pop())

def fillup(i):
    while len(tubes[i]) < 3: move(n, i)

# intentionally slow
def other(i):
    for j in range(i+1, n+1):
        if j != i and tubes[i][0] in tubes[j]:
            return j

def fix2(i):
    clr = tubes[i][0]
    if tubes[i][1] == clr: return

    j = other(i)

    move(i, n)
    move(i, n)
    while tubes[j][-1] != clr: move(j, i)
    move(j, n)
    while len(tubes[i]) > 1: move(i, j)
    move(n, i)
    fillup(i)
    fillup(j)

def fix3(i):
    clr = tubes[i][0]
    if tubes[i][2] == clr: return

    j = other(i)

    move(i, n)
    while tubes[j][-1] != clr: move(j, n)
    move(j, i)
    fillup(j)

n = int(input())

tubes = []
output = []
for _ in range(n+1):
    t = list(map(int, input().split()))
    while t and t[-1] == 0: t.pop()
    tubes.append(t)

for i in range(n): fillup(i)

for i in range(n):
    fix2(i)
    fix3(i)

print(len(output))
for t in output: print(*t)
