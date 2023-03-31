#!/usr/bin/python3

R,F = map(int,input().split())

turns = F // R
rem = F % R
if rem > R/2:
    turns += 1

if turns % 2 == 0:
    print("up")
else:
    print("down")

