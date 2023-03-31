#!/bin/python3

# An O(n log n) solution. Adapts KACTL segtree implementation:
# https://github.com/kth-competitive-programming/kactl

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

ans = [-1]*n
psum = 0

tree = [0]*(2*n)

def update(i, x):
    i += n
    tree[i] = x
    while i > 1:
        i >>= 1
        tree[i] = tree[2*i] + tree[2*i+1]

def query(b, e):
    rb, re = 0, 0
    b, e = b+n, e+n
    while b < e:
        if b&1:
            rb += tree[b]
            b += 1
        if e&1:
            e -= 1
            re += tree[e]
        b >>= 1
        e >>= 1
    return rb+re


for p in po:
    ib = i_to_b[p.i]
    ans[p.i] = psum - query(ib, n)
    update(ib, p.v)
    psum += p.v

print(*ans, sep="\n")
