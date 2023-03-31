#!/usr/bin/env python3
N,D=map(int,input().split())
mess,clean=[-1]*N,[-1]*N
for i in range(N):
    mess[i],clean[i]=map(int,input().split())
visitlist=[int(input()) for _ in range(D)]
visit=[0]*(N+1)
for i in visitlist:
    visit[i] = 1
dp=[999999999]*((N+1)**2)

M=N+1
lastvisit = max(visitlist)-1
for m in range(0, N+1):
    dp[m*M] = 0
for i in range(0, lastvisit+1):
    if not visit[i+1]:
        dp[i+1] = min(dp[i+1], dp[i]+mess[i]) # don't clean (when we have no cleaning days left)
        for m in range(1, N+1):
            dp[i+1+m*M] = min(dp[i+1+m*M], dp[i+m*M]+mess[i]) # don't clean
            dp[i+1+m*M] = min(dp[i+1+m*M], max(dp[i+(m-1)*M]+mess[i]-clean[i], 0)) # clean
    else:
        if dp[i]+mess[i] == 0: dp[i+1] = 0
        for m in range(1, N+1):
            if dp[i+m*M]+mess[i] == 0: dp[i+1+m*M] = 0
            if max(dp[i+(m-1)*M]+mess[i]-clean[i], 0) == 0: dp[i+1+m*M] = 0

# binary searching over 1000 elements is pointless, but here it is anyway...
lo = 0
hi = N
while hi-lo > 1:
    m = (lo+hi)//2
    if dp[lastvisit+1+m*M] == 0: hi = m
    else: lo = m
if dp[lastvisit+1+lo*M] == 0:
    hi = lo
print(hi if dp[lastvisit+1+hi*M] == 0 else -1)
