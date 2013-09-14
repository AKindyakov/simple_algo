#!/bin/env python
#-*- utf-8 -*-

#---------------------------------------
import sys
#---------------------------------------

def getPrime(maxN):
    blank = [ True for n in range(0, maxN)]
    for n in range(2,maxN+1):
        for d in range(2, maxN+1):
            if n != d and n%d == 0:
                blank[n-1]=False
    
    ret = []
    for n in range(len(blank)):
        if blank[n] :
            ret.append(n+1)
    return ret

for arg in sys.argv:
    if str.isdigit(arg):
        print getPrime(int(arg))

