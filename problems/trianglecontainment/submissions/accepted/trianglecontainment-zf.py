#!/bin/python3

# An O(n^{1.5}) solution using sqrt decomp

class Point:
    def __init__(self, x, y, v, i):
        self.x, self.y, self.v, self.i = x, y, v, i

    def __lt__(self, q):
        return self.x*q.y > self.y*q.x

n, bx = map(int, input().split())
po, pb = [], []

for i in range(n):
    x, y, v = map(int, input().split())
    po.append(Point(x, y, v, i))
    pb.append(Point(x-bx, y, v, i))


po.sort()
pb.sort()
pb = pb[::-1]

i_to_b = [0]*n
for i in range(n): i_to_b[pb[i].i] = i


B = 320 # about sqrt(MAXN)
val, block = [0]*n, [0]*(n//B+1)
ans = [-1]*n
psum = 0

for p in po:
    ib = i_to_b[p.i]

    psum2 = 0
    j = ib
    while j%B and j < n:
        psum2 += val[j]
        j += 1
    while j < n:
        psum2 += block[j//B]
        j += B

    ans[p.i] = psum - psum2

    val[ib] = p.v
    block[ib//B] += p.v
    psum += p.v

print(*ans, sep="\n")
