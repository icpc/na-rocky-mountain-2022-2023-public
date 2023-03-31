#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**5)

N,D=map(int,input().split())
mess,clean=[-1]*N,[-1]*N
for i in range(N):
    mess[i],clean[i]=map(int,input().split())
visit=set([int(input()) for _ in range(D)])
dp=[-1]*((N+1)*N)

def solve(i, m): # the smallest amount of mess we can get if we spend m days cleaning
    if i == -1:
        return 0
    if dp[i+m*N] != -1:
        return dp[i+m*N]
    best = 9e9
    if i+1 not in visit:
        best = min(best, solve(i-1, m)+mess[i]) # no cleaning today
        if m > 0:
            best = min(best, max(solve(i-1, m-1)+mess[i]-clean[i], 0)) # clean today
    else:
        if solve(i-1, m)+mess[i] == 0:
            best = 0
        elif m > 0 and max(0, solve(i-1, m-1)+mess[i]-clean[i], 0) == 0:
            best = 0
    dp[i+m*N] = best
    return best

#print([solve(max(visit)-1,k) for k in range(N+1)])
lastvisit = max(visit)-1
lo = 0
hi = N
while hi-lo > 1:
    #print(lo, hi)
    m = (lo+hi)//2
    if solve(lastvisit, m) == 0: hi = m
    else: lo = m
if solve(lastvisit, lo) == 0:
    hi = lo
print(hi if solve(lastvisit, hi) == 0 else -1)
