#!/bin/python3

import math

r, f = map(float, input().split())

print("down" if 0.5 <= math.fmod(f/r, 2) <= 1.5 else "up")
