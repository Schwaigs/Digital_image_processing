#!/usr/bin/env python3

import matplotlib.pyplot as plt
import sys

x=[]
y=[]

for line in sys.stdin:
    data=[int(k) for k in line.split()]
    x.append(data[0])
    y.append(data[1])

plt.bar(x,y,width=0.7)
plt.show()